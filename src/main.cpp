#include <iostream>
#include <string>
#include <gpiod.h>

int enumerate_gpiod_chips()
{
    struct gpiod_chip_iter* iter;
    struct gpiod_chip* chip;

    iter = gpiod_chip_iter_new();
    if (!iter)
    {
        perror ("gpiod_chip_iter_new failure");
        return EXIT_FAILURE;
    }

    while((chip = gpiod_chip_iter_next(iter)) != NULL)
    {
        const char* name = gpiod_chip_name(chip);
        const char* label = gpiod_chip_label(chip);
        int num_lines = gpiod_chip_num_lines(chip);

        std::string sName = (name)?name : "?";
        std::string sLabel = (label)?label : "?";
        std::cout << "chip: " << sName << ", label: " << sLabel << ", lines: " << num_lines << std::endl;
    }

    gpiod_chip_iter_free(iter);
    return EXIT_SUCCESS;
}

int main()
{
    std::cout << "Enumerate chips:" << std::endl;
    enumerate_gpiod_chips();
    return 0;
}