/*====================================================================*
 -  Copyright (C) 2001 Leptonica.  All rights reserved.
 -  This software is distributed in the hope that it will be
 -  useful, but with NO WARRANTY OF ANY KIND.
 -  No author or distributor accepts responsibility to anyone for the
 -  consequences of using this software, or for whether it serves any
 -  particular purpose or works at all, unless he or she says so in
 -  writing.  Everyone is granted permission to copy, modify and
 -  redistribute this source code, for commercial or non-commercial
 -  purposes, with the following restrictions: (1) the origin of this
 -  source code must not be misrepresented; (2) modified versions must
 -  be plainly marked as such; and (3) this notice may not be removed
 -  or altered from any source or modified source distribution.
 *====================================================================*/

/*
 *   dewarptest1.c
 *
 *   This exercise functions in dewarp.c for dewarping based on lines
 *   of horizontal text.  It also creates a 24-image pdf of steps
 *   in the process.
 */

#include "allheaders.h"

#define   DO_QUAD     1
#define   DO_CUBIC    0
#define   DO_QUARTIC  0

l_int32 main(int    argc,
             char **argv)
{
l_int32     i, n, ignore;
l_float32   a, b, c, d, e;
L_DEWARP   *dew1, *dew2;
L_DEWARPA  *dewa;
FILE       *fp;
FPIX       *fpix;
NUMA       *nax, *nay, *nafit;
PIX        *pixs, *pixn, *pixg, *pixb, *pixt1, *pixt2, *pixt3;
PIX        *pixs2, *pixn2, *pixg2, *pixb2;
PTA        *pta, *ptad;
PTAA       *ptaa1, *ptaa2;

/*    pixs = pixRead("1555-7.jpg"); */
    pixs = pixRead("cat-35.jpg");
/*    pixs = pixRead("cat-10.jpg"); */

        /* Normalize for varying background and binarize */
    pixn = pixBackgroundNormSimple(pixs, NULL, NULL);
    pixg = pixConvertRGBToGray(pixn, 0.5, 0.3, 0.2);
    pixb = pixThresholdToBinary(pixg, 130);

        /* Run the basic functions */
    dewa = dewarpaCreate(2, 30, 1, 10, 30);
    dew1 = dewarpCreate(pixb, 10);
    dewarpaInsertDewarp(dewa, dew1);
    dewarpBuildModel(dew1, "/tmp/dewarp_model1.pdf");
    dewarpaApplyDisparity(dewa, 10, pixg, "/tmp/dewarp_apply1.pdf");

         /* Write out some of the files to be imaged */
    lept_rmdir("dewtest");
    lept_mkdir("dewtest");
    pixWrite("/tmp/dewtest/001.jpg", pixs, IFF_JFIF_JPEG);
    pixWrite("/tmp/dewtest/002.jpg", pixn, IFF_JFIF_JPEG);
    pixWrite("/tmp/dewtest/003.jpg", pixg, IFF_JFIF_JPEG);
    pixWrite("/tmp/dewtest/004.png", pixb, IFF_TIFF_G4);
    pixt1 = pixRead("/tmp/dewmod/002.png");
    pixWrite("/tmp/dewtest/006.png", pixt1, IFF_PNG);
    pixDestroy(&pixt1);
    pixt1 = pixRead("/tmp/dewmod/003.png");
    pixWrite("/tmp/dewtest/007.png", pixt1, IFF_PNG);
    pixDestroy(&pixt1);
    pixt1 = pixRead("/tmp/dewmod/006.png");
    pixWrite("/tmp/dewtest/008.png", pixt1, IFF_PNG);
    pixDestroy(&pixt1);
    pixt1 = pixRead("/tmp/dewmod/007.png");
    pixWrite("/tmp/dewtest/009.png", pixt1, IFF_PNG);
    pixDestroy(&pixt1);
    pixt1 = pixRead("/tmp/dewapply/002.png");
    pixWrite("/tmp/dewtest/010.png", pixt1, IFF_PNG);
    pixDestroy(&pixt1);
    pixt1 = pixRead("/tmp/dewapply/003.png");
    pixWrite("/tmp/dewtest/011.png", pixt1, IFF_PNG);
    pixt2 = pixThresholdToBinary(pixt1, 130);
    pixWrite("/tmp/dewtest/012.png", pixt2, IFF_TIFF_G4);
    pixDestroy(&pixt1);
    pixDestroy(&pixt2);
    pixt1 = pixRead("/tmp/dewmod/004a.png");
    pixWrite("/tmp/dewtest/013.png", pixt1, IFF_PNG);
    pixDestroy(&pixt1);
    pixt1 = pixRead("/tmp/dewmod/004b.png");
    pixWrite("/tmp/dewtest/014.png", pixt1, IFF_PNG);
    pixDestroy(&pixt1);
    pixt1 = pixRead("/tmp/dewmod/005a.png");
    pixWrite("/tmp/dewtest/015.png", pixt1, IFF_PNG);
    pixDestroy(&pixt1);
    pixt1 = pixRead("/tmp/dewmod/005b.png");
    pixWrite("/tmp/dewtest/016.png", pixt1, IFF_PNG);
    pixDestroy(&pixt1);

        /* Normalize another image, that may not have enough textlines
         * to build an accurate model */
/*    pixs2 = pixRead("1555-3.jpg");  */
    pixs2 = pixRead("cat-7.jpg");
/*    pixs2 = pixRead("cat-14.jpg"); */
    pixn2 = pixBackgroundNormSimple(pixs2, NULL, NULL);
    pixg2 = pixConvertRGBToGray(pixn2, 0.5, 0.3, 0.2);
    pixb2 = pixThresholdToBinary(pixg2, 130);

        /* Apply the previous disparity model to this image */
    dew2 = dewarpCreate(pixb2, 14);
    dewarpaInsertDewarp(dewa, dew2);
    dewarpaInsertRefModels(dewa, 1);
/*    dewarpaInfo(stderr, dewa); */
    dewarpaApplyDisparity(dewa, 14, pixg2, "/tmp/dewarp_apply2.pdf");
    dewarpaDestroy(&dewa);

        /* Write out files for the second image */
    pixWrite("/tmp/dewtest/017.jpg", pixs2, IFF_JFIF_JPEG);
    pixWrite("/tmp/dewtest/018.jpg", pixg2, IFF_JFIF_JPEG);
    pixWrite("/tmp/dewtest/019.png", pixb2, IFF_TIFF_G4);
    pixt1 = pixRead("/tmp/dewmod/006.png");
    pixWrite("/tmp/dewtest/020.png", pixt1, IFF_PNG);
    pixDestroy(&pixt1);
    pixt1 = pixRead("/tmp/dewapply/002.png");
    pixWrite("/tmp/dewtest/021.png", pixt1, IFF_PNG);
    pixt2 = pixThresholdToBinary(pixt1, 130);
    pixWrite("/tmp/dewtest/022.png", pixt2, IFF_TIFF_G4);
    pixDestroy(&pixt1);
    pixDestroy(&pixt2);
    pixt1 = pixRead("/tmp/dewmod/007.png");
    pixWrite("/tmp/dewtest/023.png", pixt1, IFF_PNG);
    pixDestroy(&pixt1);
    pixt1 = pixRead("/tmp/dewapply/003.png");
    pixWrite("/tmp/dewtest/024.png", pixt1, IFF_PNG);
    pixt2 = pixThresholdToBinary(pixt1, 130);
    pixWrite("/tmp/dewtest/025.png", pixt2, IFF_TIFF_G4);
    pixDestroy(&pixt1);
    pixDestroy(&pixt2);

        /* Generate the big pdf file */
    convertFilesToPdf("/tmp/dewtest", NULL, 135, 1.0, 0, 0, "Dewarp Test",
                      "/tmp/dewarp.pdf");
    fprintf(stderr, "pdf file made: /tmp/dewarp.pdf\n");

    pixDestroy(&pixs);
    pixDestroy(&pixn);
    pixDestroy(&pixg);
    pixDestroy(&pixb);
    pixDestroy(&pixs2);
    pixDestroy(&pixn2);
    pixDestroy(&pixg2);
    pixDestroy(&pixb2);
    return 0;
}
