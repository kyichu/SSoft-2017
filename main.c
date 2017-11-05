#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cJSON.h"

void showHelpMessage() {
        printf("Usage:\tSSoft-2017 [[SLICE1]..]\n");
        printf("\n\tYou may input as many file names as desired\n");
}

int main(int argc, char *argv[]) {

        cJSON **slices_json;
        FILE *slice_file;
        char *slice_str;
        int slice_size = 0;
        int ret = 0;

        if(argc < 2) {
                printf("ERROR: No input\n");
                showHelpMessage();
                return 1;
        }

        if(!strncmp(argv[1], "-h", 2)){
                showHelpMessage();
                return 0;
        }

        /*
         * Allocates enough cJSON pointers to parse all of the slices
         */

        slices_json = (cJSON **) malloc (sizeof(cJSON *) * (argc - 1));

        /*
         * Reads each file one by one and parses them into a cJSON structure
         */

        for(int i = 1; i < argc; i++) {
                slice_file = fopen(argv[i], "r");
                if(slice_file == NULL){
                        printf("Error opening file %s\n", argv[i]);
                        free(slices_json);
                        return 1;
                }

                fseek(slice_file, 0L, SEEK_END);
                slice_size = ftell(slice_file);
                rewind(slice_file);

                slice_str = (char *) malloc(sizeof(char) * slice_size);

                ret = fread(slice_str, sizeof(char), slice_size, slice_file);
                if(ret != slice_size) {
                        printf("Error reading file %s\n", argv[i]);
                        free(slices_json);
                        fclose(slice_file);
                        return 1;
                }

                slices_json[i-1] = cJSON_Parse(slice_str);

                fclose(slice_file);
        }

        free(slices_json);
        return 0;

}
