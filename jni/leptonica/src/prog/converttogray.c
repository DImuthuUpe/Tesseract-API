/*====================================================================*
 -  Copyright (C) 2001 Leptonica.  All rights reserved.
 -
 -  Redistribution and use in source and binary forms, with or without
 -  modification, are permitted provided that the following conditions
 -  are met:
 -  1. Redistributions of source code must retain the above copyright
 -     notice, this list of conditions and the following disclaimer.
 -  2. Redistributions in binary form must reproduce the above
 -     copyright notice, this list of conditions and the following
 -     disclaimer in the documentation and/or other materials
 -     provided with the distribution.
 -
 -  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 -  ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 -  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 -  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL ANY
 -  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 -  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 -  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 -  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 -  OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 -  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 -  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *====================================================================*/

/*
 * converttogray.c
 *
 */

#include "allheaders.h"

main(int    argc,
     char **argv)
{
char         *filein, *fileout;
l_int32       d, same;
PIX          *pixs, *pixd, *pixt0, *pixt1, *pixt2, *pixt3, *pixt4, *pixt5;
static char   mainName[] = "converttogray";

    if (argc != 2 && argc != 3)
	exit(ERROR_INT(" Syntax:  converttogray filein [fileout]",
	               mainName, 1));

    filein = argv[1];
    fileout = argv[2];

    if ((pixs = pixRead(filein)) == NULL)
	exit(ERROR_INT("pixs not made", mainName, 1));

#if 0
    pixd = pixConvertRGBToGray(pixs, 0.33, 0.34, 0.33);
    pixWrite(fileout, pixd, IFF_PNG);
    pixDestroy(&pixd);
#endif

#if 1
    d = pixGetDepth(pixs);
    if (d == 2) {
	pixt1 = pixConvert2To8(pixs, 0x00, 0x55, 0xaa, 0xff, TRUE);
	pixt2 = pixConvert2To8(pixs, 0x00, 0x55, 0xaa, 0xff, FALSE);
	pixEqual(pixt1, pixt2, &same);
	if (same)
	    fprintf(stderr, "images are the same\n");
	else
	    fprintf(stderr, "images are different!\n");
	pixWrite("/tmp/junkpixt1", pixt1, IFF_PNG);
	pixWrite("/tmp/junkpixt2", pixt2, IFF_PNG);
	pixDestroy(&pixt1);
	pixDestroy(&pixt2);
	pixSetColormap(pixs, NULL);
	pixt3 = pixConvert2To8(pixs, 0x00, 0x55, 0xaa, 0xff, TRUE);
	pixt4 = pixConvert2To8(pixs, 0x00, 0x55, 0xaa, 0xff, FALSE);
	pixEqual(pixt3, pixt4, &same);
	if (same)
	    fprintf(stderr, "images are the same\n");
	else
	    fprintf(stderr, "images are different!\n");
	pixWrite("/tmp/junkpixt3", pixt3, IFF_PNG);
	pixWrite("/tmp/junkpixt4", pixt4, IFF_PNG);
	pixDestroy(&pixt3);
	pixDestroy(&pixt4);
    }
    else if (d == 4) {
	pixt1 = pixConvert4To8(pixs, TRUE);
	pixt2 = pixConvert4To8(pixs, FALSE);
	pixEqual(pixt1, pixt2, &same);
	if (same)
	    fprintf(stderr, "images are the same\n");
	else
	    fprintf(stderr, "images are different!\n");
	pixWrite("/tmp/junkpixt1", pixt1, IFF_PNG);
	pixWrite("/tmp/junkpixt2", pixt2, IFF_PNG);
	pixDestroy(&pixt1);
	pixDestroy(&pixt2);
	pixSetColormap(pixs, NULL);
	pixt3 = pixConvert4To8(pixs, TRUE);
	pixt4 = pixConvert4To8(pixs, FALSE);
	pixEqual(pixt3, pixt4, &same);
	if (same)
	    fprintf(stderr, "images are the same\n");
	else
	    fprintf(stderr, "images are different!\n");
	pixWrite("/tmp/junkpixt3", pixt3, IFF_PNG);
	pixWrite("/tmp/junkpixt4", pixt4, IFF_PNG);
	pixDestroy(&pixt3);
	pixDestroy(&pixt4);
    }
#endif

    pixDestroy(&pixs);
    return 0;
}

