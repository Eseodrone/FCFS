/**
  Mon premier programme en assembleur
  Sujet de TD - ESEO 2013
  @Author: Samuel Poiraud
  @Student: METTEZ VOTRE NOM ICI
  @Date : ...
  */

  .syntax unified
  .cpu cortex-m3
  .fpu softvfp
  .thumb


.data				//Déclaration des labels des variables / tableaux...
	variable_int: .space 4		//Une variable en int occupe 4 octets en mémoire

	variable_byte: .space 1		//Une variable d'un octet

	.set TAB_SIZE,	6	//Equivalent d'un "#define TAB_SIZE 6"
	variable_tableau: .space TAB_SIZE
	variable_int2: .space 4
	chaine1: .asciz "chêne"
	chaine2: .asciz "érable"
	chaine3: .asciz "hêtre"

.section  .text.User_section	//Les instructions assembleur commencent ici.

.global asm_main	//Déclare que le label main_asm est également accessible de l'extérieur du fichier assembler. (en C, on parle de fonction "publique").
asm_main:

//Mission 0
	BL M0_useless_function

//Mission 1
	MOV R0, #21
	//MOV R0, #-3
	//MOV R0, #18
	BL M1_ecrete_note

//Mission 2
	BL M2_incremente_variable_int

//Mission 3
	MOV R2, #'A'		//Le caractère à mettre dans le tableau
	MOV R1, #TAB_SIZE	//La taille du tableau (en nombre de char), ici, TAB_SIZE est défini à 6
	LDR R0,=variable_tableau
	BL M3_init_tab

infinite_loop:
	B infinite_loop



M0_useless_function:
	//Choix arbitraire, A : R0, B : R1, C : R2
	MOV R0, #3		// a = 3
	MOV R1, R0		// b = a
	ADD R2, R0, R1	// c = a + b
	MOV r3, #4
	MUL R1, R1, R3	// b = b*4. Une multiplication ne se fait qu'avec des registres entre eux.
	MOV pc, lr		//retourne à l'appelant.


// la note à écreter est placée dans R0, la note ecretée est remise aussi dans R0.
M1_ecrete_note:
	CMP R0, #20		//Comparaison de la note avec 20
	BLE ici			//On saute l'instruction suivante pour rejoindre "ici" si la comparaison "<=" est vraie
	MOV R0, #20		//on met 20 dans note.
ici:
	CMP R0, #0		//Comparaison de la note avec 0
	BGE la			//On saute l'instruction suivante pour rejoindre "ici" si la comparaison ">=" est vraie
	MOV R0, #0		//On met 0 dans note.
la:
	MOV PC, LR		//return


M1_bis_ecrete_note:
	CMP R0, #20		//Comparaison de la note avec 20
	IT GT
	MOVGT R0, #20		//on met 20 dans note si note>20.
	CMP R0, #0		//Comparaison de la note avec 0
	IT LT
	MOVLT R0, #0		//On met 0 dans note si note<0
	MOV PC, LR		//return


M2_incremente_variable_int:
	LDR R0, =variable_int
	LDR R1, [R0]
	ADD R1, R1, #1
	STR R1, [R0]
	MOV PC, LR

//Dans R0 : l'adresse du tableau
//Dans R1 : la taille du tableau
//Dans R2 : l'octet à ranger dans chaque case du tableau
//Vous pouvez mettre i dans R3
M3_init_tab:
	MOV r3, #0		//i = 0
init_tab_loop:
	STRB r2, [r0]	//Stocke i dans le tableau
	ADD r0, r0, #1	//Incrémente le pointeur du tableau
	ADD r3, r3, #1	//incrémente i
	CMP r3, r1		//Compare i à "size"
	BNE init_tab_loop	//Si i!=size, on recommence
	MOV PC, LR		//return

//Retourne la taille d'une chaine de caractères
my_strlen:
	MOV R1, R0			//Copie de l'adresse de la chaine
my_strlen_loop:
	LDRB R2, [R1], #1	//Lecture dans R2 de l'octet pointé par R1, puis incrémentation de R1
	CMP R2, #0			//Est-ce que le caractère lu est 0 ?
	BNE my_strlen_loop 	//On reboucle si on est pas à la fin
	SUB R0, R1, R0		//Nombre de caractères = adresse finale - adresse initiale
	SUB R0, #1
	MOV PC, LR

		//Remarque : ce sous-programme est bogué volontairement...
.global TD_mission_scratch
TD_mission_scratch:
	PUSH {R4,LR}
	MOV R4, #0			//J'initialise la somme

	LDR R0,=chaine1
	BL my_strlen
	ADD R4, R0			//J'ajoute la taille de chaine1 à la somme

	LDR R0,=chaine2
	BL my_strlen
	ADD R4, R0			//J'ajoute la taille de chaine2 à la somme

	LDR R0,=chaine3
	BL my_strlen
	ADD R0, R4			//J'ajoute la taille de chaine3 à la somme

	POP {R4,LR}
	MOV PC, LR




.global additionner_7
additionner_7:
	add r0, r0, r1
	add r0, r0, r2
	add r0, r0, r3

	mov ip, sp

	ldrb r1, [ip]
	add r0, r0, r1
	add ip, #4

	ldrb r1, [ip]
	add r0, r0, r1
	add ip, #4

	ldrb r1, [ip]
	add r0, r0, r1

	and r0, #0xFF

	mov pc, lr



.global additionner_n
additionner_n:
	ADD R1, R1, R2

	CMP R0, #2
	ITE GT
	ADDGT R1, R3	//Si n > 2, il faut chercher le terme suivant
	BLE additionner_n_fin	//si n <= 2, c'est fini

	SUBS R0, #3		//On retire 3 à n
	IT	EQ
	BEQ additionner_n_fin	//si n <= 2, c'est fini

	MOV IP, SP		//Copie locale du pointeur de pile
additionner_n_loop:
	LDR R2, [IP]	//On va chercher le prochain terme
	ADD R1, R2		//On ajoute le prochain terme
	ADD IP, #4		//On pointe vers le terme suivant
	SUBS R0, #1 	//On retire 1 à n, et on met à jour le CPSR pour savoir si on a atteint 0.
	BNE additionner_n_loop	//Il reste des termes...
additionner_n_fin:
	MOV R0, R1
	MOV PC, LR




.global factorielle_n
factorielle_n:
	CMP R0, #1
	ITT LE
	MOVLE R0, #1
	MOVLE PC, LR

	STMDB SP!, {R4, LR}
	MOV R4, R0			//On conserve n dans un registre non scratchable
	SUB R0, R0, #1		//On calcule n-1
	BL factorielle_n	//Appel récursif
	MUL R1, R0, R4		//Multiplication
	MOV R0, R1			//on déplace le résultat pour le renvoyer

	LDMIA SP!, {R4, LR}
	MOV PC, LR


