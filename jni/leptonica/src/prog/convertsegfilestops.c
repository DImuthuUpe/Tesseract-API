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
 * convertsegfilestops.c
 *
 *    Converts all image files in a 'page' directory, using optional
 *    corresponding segmentation mask files in a 'mask' directory,
 *    to a level 2 compressed PostScript file.  This is done
 *    automatically at a resolution that fits to a letter-sized
 *    (8.5 x 11) inch page.  The 'page' and 'mask' files are paired
 *    by having the same number embedded in their name.
 *    The 'numpre' and 'numpost' args specify the number of
 *    characters at the beginning and end of the filename (not
 *    counting any extension) that are NOT part of the page number.
 *    For example, if the page numbers are 00000.jpg, 00001.jpg, ...
 *    then numpre = numpost = 0.
 *
 *    The mask directory must exist, but it does not need to have
 *    any image mask files.
 *
 *    The pages are taken in lexical order of the filenames.  Therefore,
 *    the embedded numbers should be 0-padded on the left up to
 *    a fixed number of digits.
 *
 *    PostScript (and pdf) allow regions of the image to be encoded
 *    differently.  Regions can be over-written, with the last writing
 *    determining the final output.  Black "ink" can also be written
 *    through a mask that is given by a 1 bpp image.
 *
 *    The page images are typically grayscale or color.  To take advantage
 *    of this depth, one typically upscales the text by 2.0.  Likewise,
 *    the images regions, denoted by foreground in the corresponding
 *    segmentation mask, can be rendered at lower resolution, and
 *    it is often useful to downscale the image parts by 0.5.
 *
 *    If the mask does not exist, the entire page is interpreted as
 *    text; it is converted to 1 bpp and written to file with
 *    ccitt-g4 compression at the requested "textscale" relative
 *    to the page image.   If the mask exists and the foreground
 *    covers the entire page, the entire page is saved with jpeg
 *    ("dct") compression at the requested "imagescale".
 *    If the mask exists and partially covers the page image, the
 *    page is saved as a mixture of grayscale or rgb dct and 1 bpp g4.
 *
 *    This uses a single global threshold for binarizing the text
 *    (i.e., non-image) regions of every page.
 */

#include <string.h>
#include "allheaders.h"

main(int    argc,
     char **argv)
{
char      *pagedir, *pagestr, *maskdir, *maskstr, *fileout;
l_int32    threshold, numpre, numpost, maxnum;
l_float32  textscale, imagescale;

    if (argc != 12) {
	fprintf(stderr,
            " Syntax: convertsegfilestops pagedir pagestr maskdir maskstr \\ \n"
            "                             numpre numpost maxnum \\ \n"
            "                             textscale imagescale thresh fileout\n"
            "     where\n"
            "         pagedir:  Input directory for page image files\n"
            "         pagestr:  Substring for matching; use 'allfiles' to\n"
            "                   convert all files in the page directory\n"
            "         maskdir:  Input directory for mask image files\n"
            "         maskstr:  Substring for matching; use 'allfiles' to\n"
            "                   convert all files in the mask directory\n"
            "         numpre:  Number of characters in name before number\n"
            "         numpost:  Number of characters in name after number\n"
            "         maxnum:  Only consider page numbers up to this value\n"
            "         textscale:  Scale of text output relative to pixs\n"
            "         imagescale:  Scale of image output relative to pixs\n"
            "         thresh:  threshold for binarization; typically about\n"
            "                  180; use 0 for default\n"
            "         fileout:  Output p file\n");
        return 1;
    }

    pagedir = argv[1];
    pagestr = argv[2];
    maskdir = argv[3];
    maskstr = argv[4];
    numpre = atoi(argv[5]);
    numpost = atoi(argv[6]);
    maxnum = atoi(argv[7]);
    textscale = atof(argv[8]);
    imagescale = atof(argv[9]);
    threshold = atoi(argv[10]);
    fileout = argv[11];

    if (!strcmp(pagestr, "allfiles"))
        pagestr = NULL;
    if (!strcmp(maskstr, "allfiles"))
        maskstr = NULL;

    return convertSegmentedPagesToPS(pagedir, pagestr, maskdir, maskstr,
                                     numpre, numpost, maxnum, textscale,
                                     imagescale, threshold, fileout);
}


