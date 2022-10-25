#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "./headers//stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers//stb_image_write.h"

unsigned char background_subtraction(unsigned char *background_1, unsigned char *background_2, unsigned char *observed_image, int width, int height, int channel)
{
    for (int i = 0; i < height ; i++){
        for (int j = 0; j < width ; j++){
            int threshold = 0;
            for(int k = 0 ; k < channel ; k++){
                threshold += abs(observed_image[i * width * channel + j * channel + k] - background_1[i * width * channel + j * channel + k]);
            }
            if(threshold > 175)
            {
                for(int k = 0 ; k < channel ; k++)
                {
                    background_2[i * width * channel + j * channel + k] = observed_image[i * width * channel + j * channel + k];
                }
            }
        }
    }
}
int main(){
    //declare vars
    int width, height, channel;
    char image_1[] = "./images//background.jpg";
    char image_2[] = "./images//weather_forecast.jpg";
    char image_3[] = "./images//foreground.jpg";
    char new_image[] = "./images//new_image.jpg";

    //read image data
    unsigned char *background_1 = stbi_load(image_1, &width, &height, &channel, 0);
    printf("Width = %d\nHeight = %d\nChannel = %d\n", width, height, channel);
    unsigned char *background_2 = stbi_load(image_2, &width, &height, &channel, 0);
    printf("Width = %d\nHeight = %d\nChannel = %d\n", width, height, channel);
    unsigned char *observed_image = stbi_load(image_3, &width, &height, &channel, 0);
    printf("Width = %d\nHeight = %d\nChannel = %d\n", width, height, channel);
    if (background_1 == NULL || background_2 == NULL || observed_image == NULL) {
        printf("\nError in loading the image\n");
        exit(1);
    }
    

    background_subtraction(background_1, background_2, observed_image, width, height, channel);

    //save image
    stbi_write_jpg(new_image, width, height, channel, background_2, width * channel);
    printf("New image save to %s\n", new_image);
}