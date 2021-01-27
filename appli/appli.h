/*
 * appli.h
 *
 *  Created on: 1 avr. 2015
 *      Author: Nirgal
 */

#ifndef APPLI_H_
#define APPLI_H_


/*
 * @brief Initialisation de notre application, et des périphériques qu'elle utilise.
 * @pre : cette fonction doit être appelée préalablement à tout autre appel de fonction de cette classe.
 */
void APPLI_init(void);

/*
 * @brief Boucle de tâche de fond de l'application
 * @pre : doit être appelée régulièrement.
 */
void APPLI_process_main(void);

/*
 * @brief Routine d'it de l'application.
 * @pre : cette fonction doit être appelée toutes les ms.
 */
void APPLI_process_1ms(void);


#endif /* APPLI_H_ */
