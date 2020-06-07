#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "defines.h"


void run_as_cameriere(MYSQL *conn)
{
	char options[15] = {'1','2','3','4','5','6','7','8','9','10','11','12','13','14'};
	char op;
	
	printf("Passo al ruolo di cameriere...\n");

	if(!parse_config("users/barman.json", &conf)) {
		fprintf(stderr, "Unable to load cameriere configuration\n");
		exit(EXIT_FAILURE);
	}

	if(mysql_change_user(conn, conf.db_username, conf.db_password, conf.database)) {
		fprintf(stderr, "mysql_change_user() failed\n");
		exit(EXIT_FAILURE);
	}

	while(true) {
		printf("\033[2J\033[H");
		printf("*** Cosa posso fare per te? ***\n\n");
		printf("1) Visualizza tavoli associati");
		printf("2) Registra ordine pizza");
		printf("3) Registra ordine pizza plus");
		printf("4) Registra ordine bevanda");
		printf("5) Visualizza ordini pizza espletati");
		printf("6) Visualizza ordini pizza plus espletati");
		printf("7) Visualizza ordini bevanda espletati");
		printf("8) Consegna ordine pizza");
		printf("9) Consegna ordine pizza plus");
		printf("10) Consegna ordine bevanda");
		printf("11) Visualizza menu' pizza");
		printf("12) Visualizza menu' bevanda");
		printf("13) Visualizza menu' ingrediente");
		printf("14) Quit\n");

		op = multiChoice("Seleziona un opzione", options, 14);

		switch(op) {

			case '1':
				visualizza_info_tavoli_associati(conn);
				break;
			case '2':
				registra_ordine_pizza(conn);
				break;
			case '3':
				registra_ordine_pizza_plus(conn);
				break;
			case '4':
				registra_ordine_bevanda(conn);
				break;
			case '5':
				visualizza_ordini_espletati_pizza(conn);
				break;
			case '6':
				visualizza_ordini_espletati_pizza_plus(conn);
				break;
			case '7':
				visualizza_ordini_espletati_bevanda(conn);
				break;
			case '8':
				consegna_ordine_pizza(conn);
				break;
			case '9':
				consegna_ordine_pizza_plus(conn);
				break;
			case '10':
				consegna_ordine_bevanda(conn);
				break;
			case '11':
				visualizza_menu_pizze(conn);
				break;
			case '12':
				visualizza_menu_bevande(conn);
				break;
			case '13':
				visualizza_menu_ingredienti(conn);
				break;
			case '14':
				return;
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

		getchar();
	}
}
