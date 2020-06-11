#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "defines.h"


static void prendi_in_carico_ordine_bevanda(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	char ok[2];

	// Input for the registration routine
	long long int id_ordine;

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_ordini_bevanda_da_espletare()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_ordini_bevanda_da_espletare statement\n", false);
	}
	

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_ordini_bevanda_da_espletare\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nLista delle bevande da espletare");
	mysql_stmt_close(prepared_stmt);


	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call prendi_in_carico_ordine_bevanda(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prendi_in_carico_ordine_bevanda statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	printf("\nID ordine: ");
	if(scanf("%lld", &id_ordine)<1){
		printf("Errore nell'acquisire indice ordine\n");
		return;
	}


	param[0].buffer_type = MYSQL_TYPE_LONGLONG;
	param[0].buffer = &id_ordine;
	param[0].buffer_length = sizeof(id_ordine);
	

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for prendi_in_carico_ordine_bevanda\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore nel prendere in carico ordine bevanda.\n");
	} else {
		printf("Ordine bevanda preso in carico correttamente\n");
	}

	mysql_stmt_close(prepared_stmt);

check_ok_bevanda:
	//espleta ordine
	printf("Digitare ok per espletare l'ordine\n");
	if(scanf("%s", ok)<1){
		printf("Errore nella conferma\n");
		goto check_ok_bevanda;
	}

	if(strcmp(ok,"ok")!=0){
		printf("Per favore digita ok\n");
		goto check_ok_bevanda;
	}

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call espleta_ordine_bevanda(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize espleta_ordine_bevanda statement\n", false);
	}

	// non vi e' reset perche i parametri sono gli stessi
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for espleta_ordine_bevanda\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore nell'espletare in carico ordine bevanda.\n");
	} else {
		printf("Ordine bevanda espletato correttamente\n");
	}

	mysql_stmt_close(prepared_stmt);

}



void run_as_barman(MYSQL *conn)
{
	char options[3] = {'1','2'};
	char op;
	
	printf("Passo al ruolo di barman...\n");

	if(!parse_config("users/barman.json", &conf)) {
		fprintf(stderr, "Unable to load barman configuration\n");
		exit(EXIT_FAILURE);
	}

	if(mysql_change_user(conn, conf.db_username, conf.db_password, conf.database)) {
		fprintf(stderr, "mysql_change_user() failed\n");
		exit(EXIT_FAILURE);
	}

	while(true) {
		printf("\033[2J\033[H");
		printf("*** Cosa posso fare per te? ***\n\n");
		printf("1) Prendi in carico ordine bevanda\n");
		printf("2) Quit\n");

		op = multiChoice("Seleziona un opzione", options, 2);

		switch(op) {

			case '1':
				prendi_in_carico_ordine_bevanda(conn);
				break;
			case '2':
				return;
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

		getchar();
	}
}
