/* x86 crtn.s */
.section .init
	/* gcc will nicely put the contents of crtend.o's .init section here. */
	popl %ebp
	ret

.section .fini
	/* gcc will nicely put the contents of crtend.o's .fini section here. */
	popl %ebp
	ret

/* x86_64 crtn.s */
//.section .init
//	/* gcc will nicely put the contents of crtend.o's .init section here. */
//	popq %rbp
//	ret

//.section .fini
//	/* gcc will nicely put the contents of crtend.o's .fini section here. */
//	popq %rbp
//	ret