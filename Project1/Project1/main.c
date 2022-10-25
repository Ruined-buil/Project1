#include <math.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"

unsigned char *uc_arrayNew_1d(int _size)
{
    return (unsigned char *)calloc(_size, sizeof(unsigned char));
}

unsigned char *merge_image(unsigned char *bg, unsigned char *fg, int width, int height, int channel)
{
    unsigned char *temp_array = uc_arrayNew_1d(width * height * channel);
    for(int i=0; i < width * height * channel; i+=3){
        if(fg[i] <= 180 && fg[i+1] <= 255 && fg[i+2] <= 100 && fg[i] >= 50 && fg[i+1] >= 150 && fg[i+2] >= 0){
            temp_array[i]=bg[i];
            temp_array[i+1]=bg[i+1];
            temp_array[i+2]=bg[i+2];
        }
        else{
            temp_array[i]=fg[i];
            temp_array[i+1]=fg[i+1];
            temp_array[i+2]=fg[i+2];
            };
    }
    return temp_array;
}

int main(){
// declare variables
    int width, height, channel;
    char path_imgbg[] = "./images/weather_forecast-resized.jpg";
    char path_imgfg[] = "./images/foreground.png";
    char save_path[] = "./images/Result.png";


    // read image data
    unsigned char *imagebg = stbi_load(path_imgbg, &width, &height, &channel, 0);
    if (imagebg == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }
    printf("BackGround: Width = %d\nHeight = %d\nChannel = %d\n\n", width, height, channel);


    unsigned char *imagefg = stbi_load(path_imgfg, &width, &height, &channel, 0);
    if (imagefg == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }
    printf("ForeGround: Width = %d\nHeight = %d\nChannel = %d\n", width, height, channel);


    unsigned char *mimage = merge_image(imagebg, imagefg, width, height, channel);
    stbi_write_png(save_path, width, height, channel, mimage, width * channel);
    printf("New image saved to %s\n", save_path);
}
