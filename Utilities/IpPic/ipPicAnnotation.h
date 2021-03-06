/*============================================================================

 Copyright (c) German Cancer Research Center (DKFZ)
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 - Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

 - Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 - All advertising materials mentioning features or use of this software must
   display the following acknowledgement:

     "This product includes software developed by the German Cancer Research
      Center (DKFZ)."

 - Neither the name of the German Cancer Research Center (DKFZ) nor the names
   of its contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE GERMAN CANCER RESEARCH CENTER (DKFZ) AND
   CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
   BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE GERMAN
   CANCER RESEARCH CENTER (DKFZ) OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
   INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
   DAMAGE.

============================================================================*/

/*
 * mitkIpPicAnnotation.h
 *---------------------------------------------------------------------
 * DESCRIPTION
 *  declarations for the annotations in the pic format
 *
 * AUTHOR & DATE
 *  Andre Schroeter	09.01.95
 *
 * UPDATES
 *  a short history of the file
 *
 *---------------------------------------------------------------------
 */

#ifndef _mitkIpPicAnnotation_h
#define _mitkIpPicAnnotation_h

typedef enum
  {
    mitkIpPicAUnknown	= 0,
    mitkIpPicAText		= 1
  } mitkIpPicAnnotationType_t;

typedef struct
  {
                mitkIpUInt4_t  _magic;

    mitkIpPicAnnotationType_t  type;

                mitkIpUInt4_t  location_x;
                mitkIpUInt4_t  location_y;

                mitkIpUInt4_t  position_x;
                mitkIpUInt4_t  position_y;
                     char *text;
  } mitkIpPicAnnotation_t;

#endif  /* _mitkIpPicAnnotation_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */

