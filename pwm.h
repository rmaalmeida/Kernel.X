// -----------------------------------------------------------------------
//   pwm.h -> funções para acesso ao pwm
//   Autor:  Rodrigo Maximiano Antunes de Almeida
//          rodrigomax at unifei.edu.br
// -----------------------------------------------------------------------
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; version 2 of the License.
// 
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// -----------------------------------------------------------------------

#ifndef PWM_H
	#define PWM_H

	void SetaPWM1(unsigned char porcento);
	void SetaPWM2(unsigned char porcento);
	void SetaFreqPWM(unsigned int freq);
	void InicializaPWM(void);


#endif //PWM_H