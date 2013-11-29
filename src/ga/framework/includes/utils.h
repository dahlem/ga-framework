/* Copyright (C) 2008 Dominik Dahlem <Dominik.Dahlem@gmail.com>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
/**
 * Declaration of utilitiy functions for the generic algorithm framework.
 *
 * @author Dominik Dahlem (ID: 02175321)
 */
#ifndef __UTILS_H__
#define __UTILS_H__

/**
 * Convert a chromosome from gray to its binary representation.
 * This code was taking from Carnegie Mellon Universities ga faq:
 * <a href="http://www.cs.cmu.edu/Groups/AI/html/faqs/ai/genetic/part6/faq-doc-1.html" /a>.
 *
 * @param unsigned short* the binary representation of the chromosome
 * @param unsigned short* the gray representation of the chromosome
 * @param int the length of the chromosome in bits
 **/
void graytobinary(unsigned short *bin, unsigned short *gray, int n);


/**
 * Convert a chromosome from binary to its representation.
 * This code was taking from Carnegie Mellon Universities ga faq:
 * <a href="http://www.cs.cmu.edu/Groups/AI/html/faqs/ai/genetic/part6/faq-doc-1.html" /a>.
 *
 * @param unsigned short* the binary representation of the chromosome
 * @param unsigned short* the gray representation of the chromosome
 * @param int the length of the chromosome in bits
 **/
void binarytogray(unsigned short *bin, unsigned short *gray, int n);


#endif /* UTILS_H */
