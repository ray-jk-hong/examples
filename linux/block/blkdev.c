#include <linux/module.h>
#include <linux/init.h>
#include <linux/blkdev.h>
#include <linux/vmalloc.h>

#define DEVICE_NAME "vblkdev"
#define SECTOR_SIZE 512
#define DEVICE_SIZE_SECTORS 2048  // 1MB设备

static struct gendisk *vdisk;
static struct request_queue *queue;
static u8 *dev_data;

static void vbdev_request(struct request_queue *q)
{
    struct request *req;
    
    while ((req = blk_fetch_request(q)) != NULL) {
        unsigned long start = blk_rq_pos(req) * SECTOR_SIZE;
        unsigned long len = blk_rq_cur_bytes(req);
        void *buffer = bio_data(req->bio);
        
        if (start + len > DEVICE_SIZE_SECTORS * SECTOR_SIZE) {
            pr_err("Request out of range\n");
            blk_mq_end_request(req, BLK_STS_IOERR);
            continue;
        }
        
        switch (req_op(req)) {
            case REQ_OP_READ:
                memcpy(buffer, dev_data + start, len);
                break;
            case REQ_OP_WRITE:
                memcpy(dev_data + start, buffer, len);
                break;
            default:
                pr_err("Unsupported operation\n");
                blk_mq_end_request(req, BLK_STS_NOTSUPP);
                continue;
        }
        
        blk_mq_end_request(req, BLK_STS_OK);
    }
}

static struct block_device_operations vbdev_fops = {
    .owner = THIS_MODULE,
};

static int __init vbdev_init(void)
{
    // 分配设备内存
    dev_data = vmalloc(DEVICE_SIZE_SECTORS * SECTOR_SIZE);
    if (!dev_data)
        return -ENOMEM;

    // 创建请求队列
    queue = blk_mq_init_sq_queue(&vbdev_tag_set, &vbdev_ops, 128, BLK_MQ_F_SHOULD_MERGE);
    if (IS_ERR(queue)) {
        vfree(dev_data);
        return PTR_ERR(queue);
    }
    blk_queue_logical_block_size(queue, SECTOR_SIZE);

    // 注册块设备
    vdisk = blk_alloc_disk(NUMA_NO_NODE);
    if (IS_ERR(vdisk)) {
        blk_cleanup_queue(queue);
        vfree(dev_data);
        return PTR_ERR(vdisk);
    }

    // 设置磁盘属性
    strscpy(vdisk->disk_name, DEVICE_NAME, DISK_NAME_LEN);
    vdisk->major = 0;  // 动态分配主设备号
    vdisk->first_minor = 0;
    vdisk->fops = &vbdev_fops;
    vdisk->queue = queue;
    set_capacity(vdisk, DEVICE_SIZE_SECTORS);

    // 激活磁盘
    add_disk(vdisk);

    pr_info("Virtual block device initialized\n");
    return 0;
}

static void __exit vbdev_exit(void)
{
    if (vdisk) {
        del_gendisk(vdisk);
        put_disk(vdisk);
    }
    if (queue)
        blk_cleanup_queue(queue);
    if (dev_data)
        vfree(dev_data);
    
    pr_info("Virtual block device removed\n");
}

module_init(vbdev_init);
module_exit(vbdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple Virtual Block Device Driver");