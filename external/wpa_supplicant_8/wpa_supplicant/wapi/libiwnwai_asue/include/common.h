// Copyright (c) 2004-2010 Atheros Communications Inc.
// All rights reserved.
//
//
// The software source and binaries included in this development package are
// licensed, not sold. You, or your company, received the package under one
// or more license agreements. The rights granted to you are specifically
// listed in these license agreement(s). All other rights remain with Atheros
// Communications, Inc., its subsidiaries, or the respective owner including
// those listed on the included copyright notices.  Distribution of any
// portion of this package must be in strict compliance with the license
// agreement(s) terms.
// </copyright>
//
// <summary>
//	WAPI supplicant for AR6002
// </summary>
//
//
//
// @file common.h
// @brief This header file contains data structures and function declarations of common, include random, alloc&free buffer, ecc, sms4, print, le&be trans

#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "os.h"



#ifndef ETH_ALEN
#define ETH_ALEN 6
#endif


typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef int s32;
typedef short s16;
typedef char s8;


#ifndef __func__
#ifdef __FUNCTION__
#define __func__  __FUNCTION__
#else
#define __func__ __FILE__
#endif
#endif


/*原来在alg_common.h中*/
void get_random(unsigned char *buffer, int len);

/*原来在config.h中*/
void *iwn_get_buffer(int len);
void *iwn_free_buffer(void *buffer, int len);

struct asue_config
{

	char as_cert_name[256];
	char user_cert_name[256];
	unsigned short used_cert;
	unsigned short pad;
};

struct _asue_cert_info {
	struct cert_obj_st_t *asue_cert_obj;
	struct asue_config config;
};

/*原来在ecc_crypt.h中*/
#define EC962_PRIVKEY_LEN	24
#define EC962_SIGN_LEN		48

int x509_ecc_verify(const unsigned char *pub_s, int pub_sl, unsigned char *in ,  int in_len, unsigned char *sign,int sign_len);
int x509_ecc_sign(const unsigned char *priv_s, int priv_sl,	const unsigned char * in, int in_len, unsigned char *out);
int x509_ecc_verify_key(const unsigned char *pub_s, int pub_sl, const unsigned char *priv_s, int priv_sl);



/*原来在sms4.h中*/
int wpi_encrypt(unsigned char * pofbiv_in, unsigned char * pbw_in, unsigned int plbw_in, unsigned char * pkey, unsigned char * pcw_out);




/*------orgin in ecc192_x962.h-------------*/
int ECC_Init(void);
int ecc192_genkey(unsigned char *priv_key, unsigned char *pub_key);
int ecc192_sign(const unsigned char *priv_key, const unsigned char *in, int in_len, unsigned char *out);
int ecc192_verify(const unsigned char * pub_key, const unsigned char * in, int in_len, const unsigned char * sign, int sign_len);
 int ecc192_ecdh(const unsigned char * priv_key, const unsigned char *pub_key, unsigned char * ecdhkey);





/* Debugging function - conditional printf and hex dump. Driver wrappers can
 *  use these for debugging purposes. */
enum { MSG_MSGDUMP=1, MSG_DEBUG, MSG_INFO, MSG_WARNING, MSG_ERROR };

#ifdef CONFIG_ANDROID_LOG

#ifdef __GNUC__
#define PRINTF_FORMAT(a,b) __attribute__ ((format (printf, (a), (b))))
#define STRUCT_PACKED __attribute__ ((packed))
#else
#define PRINTF_FORMAT(a,b)
#define STRUCT_PACKED
#endif

#define wpa_hexdump(...)            do {} while (0)

void android_printf(int level, char *format, ...)
PRINTF_FORMAT(2, 3);

#define wpa_printf android_printf

#define iwn_wpa_printf wpa_printf
#define iwn_wpa_hexdump wpa_hexdump

#else /* CONFIG_ANDROID_LOG */

#define iwn_wpa_printf wpa_printf
#define iwn_wpa_hexdump wpa_hexdump

/**
 * iwn_wpa_printf - conditional printf
 * @level: priority level (MSG_*) of the message
 * @fmt: printf format string, followed by optional arguments
 *
 * This function is used to print conditional debugging and error messages. The
 * output may be directed to stdout, stderr, and/or syslog based on
 * configuration.
 *
 * Note: New line '\n' is added to the end of the text when printing to stdout.
 */
void iwn_wpa_printf(int level, char *fmt, ...);

/**
 * iwn_wpa_hexdump - conditional hex dump
 * @level: priority level (MSG_*) of the message
 * @title: title of for the message
 * @buf: data buffer to be dumped
 * @len: length of the @buf
 *
 * This function is used to print conditional debugging and error messages. The
 * output may be directed to stdout, stderr, and/or syslog based on
 * configuration. The contents of @buf is printed out has hex dump.
 */
void iwn_wpa_hexdump(int level, const char *title, const u8 *buf, size_t len);
#endif








u16 iwn_ntohs(u16 v);
u16 iwn_htons(u16 v);

#if 0
void iwn_getshort(const void* p, void* v);
void iwn_setshort(void* p, u16 v);
#define GETSHORT(frm, v) do { iwn_getshort((frm), &(v));} while(0)
#define SETSHORT(frm, v) do { iwn_setshort((frm), (v));} while(0)

#define GETSHORT1 GETSHORT
#endif
#define	GETSHORT(frm, v) do { (v) = (((frm[0]) <<8) | (frm[1]))& 0xffff;} while (0)
#define	GETSHORT1(frm, v) do { (v) = (((frm[1]) <<8) | (frm[0]))& 0xffff;} while (0)

#define	SETSHORT(frm, v) do{(frm[0])=((v)>>8)&0xff;(frm[1])=((v))&0xff;}while(0)


void print_buf(const char* title, const void* buf, int len);

void timer_set(int t, const u8* dat, int l);
void timer_reset(void);
void timer_resend(void);


#endif /* COMMON_H */
