#include "sdcard.h"
#include "hw_config.h"
#include "ff.h"

sd_card_t* InitSD(){
    sd_card_t *psd = sd_get_by_num(0);
    FRESULT fr = f_mount(&psd->fatfs, pSD->pcName, 1);
    if (FR_OK != fr) {
        psd = null;
        panic("f_mount error: %s (%d)\n", FRESULT_str(fr), fr);
    }

    return psd;
}

void list_games(const char* path){
    FRESULT res;
    DIR dir;
    FILINFO fno;
    
    res = f_opendir(&dir, path);
    if(res == FR_OK){
        nfile = ndir = 0;
        for(;;){
            res = f_readdir(&dir, &fno);
            if(res != FR_OK || fno.fname[0] == 0) { 
                break;
            }

            if(fno.fattrib & AM_DIR) {
                // print(" <DIR> ");
            } else {
                //print("%10u %s\n", fno.fsize, fno.fname)
            }
        }
        f_closedir(&dir);
    }
}

