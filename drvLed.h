// -----------------------------------------------------------------------
//   drvLed.h -> header das definições para o driver dos LED's
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

/* Para a criação de um driver, define-se seu cabeçalho com suas funções,
 * de modo que as funções possam ser identificadas por um enumerado.
 * Além disso, uma variável de acesso ao driver deve também ser criada, sendo esta
 * a estrutura mais simples. */
// Por padronização, funções de drivers recebem parâmetros, mesmo que não os utilizem.

#ifndef drvLed_h
    #define drvLed_h
    #include "basico.h"
    #include "ddCtr_types.h"

    //apenas retorna o "objeto" do driver
    driver* getLedDriver(void);

    // define os identificadores das funções do driver
    enum {
        LED_PORTD,
        LED_END
    };

#endif // drvLed_h

