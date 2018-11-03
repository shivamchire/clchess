#ifndef DEBUG_H
#define DEBUG_H
#include <stdio.h>
/*
 * vprintn -
 * 	debug print level n with variable args
 * printn -
 * 	debug print level n with only func, line and file
 * This printf style debuging prints all printn when DEBUG is >= n
 */
#ifndef DEBUG
#define DEBUG 0
#endif
#define vprint1(fmt, ...) \
		do { \
			if (DEBUG != 0 && DEBUG <= 1) \
				fprintf(stderr, "%s:%d:%s(): " fmt"\n", \
					__FILE__, __LINE__, __func__, __VA_ARGS__); \
		} while (0)
#define vprint2(fmt, ...) \
	            do { \
			    if (DEBUG != 0 && DEBUG <= 2) \
			    	fprintf(stderr, "%s:%d:%s(): " fmt"\n", \
					__FILE__, __LINE__, __func__, __VA_ARGS__); \
		    } while (0)
#define vprint3(fmt, ...) \
	            do { \
			    if (DEBUG != 0 && DEBUG <= 3) \
			    	fprintf(stderr, "%s:%d:%s(): " fmt"\n", \
					__FILE__, __LINE__, __func__, __VA_ARGS__); \
		    } while (0)
#define vprint4(fmt, ...) \
	            do { \
			    if (DEBUG != 0 && DEBUG <= 4) \
			    	fprintf(stderr, "%s:%d:%s(): " fmt"\n", \
					__FILE__, __LINE__, __func__, __VA_ARGS__); \
		    } while (0)
#define print1(fmt, ...) \
	            do { \
			    if (DEBUG != 0 && DEBUG <= 1) \
			    	fprintf(stderr, "%s:%d:%s(): " fmt"\n", \
					__FILE__, __LINE__, __func__); \
		    } while (0)
#define print2(fmt, ...) \
	            do { \
			    if (DEBUG != 0 && DEBUG <= 2) \
			    	fprintf(stderr, "%s:%d:%s(): " fmt"\n", \
					__FILE__, __LINE__, __func__); \
		    } while (0)
#define print3(fmt, ...) \
	            do { \
			    if (DEBUG != 0 && DEBUG <= 3) \
			    	fprintf(stderr, "%s:%d:%s(): " fmt"\n", \
					__FILE__, __LINE__, __func__); \
		    } while (0)
#define print4(fmt, ...) \
	            do { \
			    if (DEBUG != 0 && DEBUG <= 4) \
			    	fprintf(stderr, "%s:%d:%s(): " fmt"\n", \
					__FILE__, __LINE__, __func__); \
		    } while (0)
#endif //#ifdef DEBUG_H
