#ifndef OUR_DRIVER_H
#define OUR_DRIVER_H

struct our_driver_data {
    int32_t internal_counter;
};


#ifdef __cplusplus
extern "C" {
#endif

void set_internal_counter(const struct device *dev, int32_t new_value);

int32_t get_internal_counter(const struct device *dev);

#ifdef __cplusplus
}
#endif

#endif // OUR_DRIVER_H
