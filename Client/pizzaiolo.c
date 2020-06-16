#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "defines.h"

static void visualizza_ordini_pizza_da_espletare(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_ordini_pizza_da_espletare()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_ordini_pizza_da_espletare statement\n", false);
	}
	

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_ordini_pizza_da_espletare\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nLista delle pizze da espletare");
	mysql_stmt_close(prepared_stmt);
}

static void espleta_ordine_pizza(MYSQL *conn, long long int ordine){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	char check[4];

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	param[0].buffer_type = MYSQL_TYPE_LONGLONG;
	param[0].buffer = &ordine;
	param[0].buffer_length = sizeof(ordine);

	check_ok_pizza:
	//espleta ordine
	printf("Digitare ok per espletare l'ordine o stop per tornare indietro\n");
	if(scanf("%s", check)<1){
		printf("Errore nella conferma\n");
		flush_stdin();
		goto check_ok_pizza;
	}
	flush_stdin();
	if((strcmp(check,"ok")!=0)&&(strcmp(check,"stop")!=0)){
		printf("Per favore digita ok\n");
		goto check_ok_pizza;
	}
	else if(strcmp(check,"stop")!=0) {
		printf("Operazione annullata\n");
		return;
	}
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call espleta_ordine_pizza(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize espleta_ordine_pizza statement\n", false);
	}

	// non vi e' reset perche i parametri sono gli stessi
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for espleta_ordine_pizza\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore nell'espletare in carico ordine pizza.\n");
	} else {
		printf("Ordine pizza espletato correttamente\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void prendi_in_carico_ordine_pizza(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	long long int id_ordine;

	visualizza_ordini_pizza_da_espletare(conn);


	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call prendi_in_carico_ordine_pizza(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prendi_in_carico_ordine_pizza statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	

	printf("\nID ordine: ");
	if(scanf("%lld", &id_ordine)<1){
		printf("Errore nell'acquisire indice ordine\n");
		flush_stdin();
		return;
	}

	flush_stdin();
	param[0].buffer_type = MYSQL_TYPE_LONGLONG;
	param[0].buffer = &id_ordine;
	param[0].buffer_length = sizeof(id_ordine);
	

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for prendi_in_carico_ordine_pizza\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore nel prendere in carico ordine pizza.\n");
	} else {
		printf("Ordine pizza preso in carico correttamente\n");
	}

	mysql_stmt_close(prepared_stmt);

	espleta_ordine_pizza(conn, id_ordine);
}

static void visualizza_ordini_pizza_plus_da_espletare(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_ordini_pizza_plus_da_espletare()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_ordini_pizza_plus_da_espletare statement\n", false);
	}


	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_ordini_pizza_plus_da_espletare\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nLista delle pizze plus da espletare");
	mysql_stmt_close(prepared_stmt);
}

static void espleta_ordine_pizza_plus(MYSQL *conn, long long int ordine){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	char check[4];

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	param[0].buffer_type = MYSQL_TYPE_LONGLONG;
	param[0].buffer = &ordine;
	param[0].buffer_length = sizeof(ordine);
	check_ok_pizza_plus:
	//espleta ordine
	printf("Digitare ok per espletare l'ordine o stop per tornare indietro\n");
	if(scanf("%s", check)<1){
		printf("Errore nella conferma\n");
		flush_stdin();
		goto check_ok_pizza_plus;
	}
	flush_stdin();
	if((strcmp(check,"ok")!=0)&&(strcmp(check,"stop")!=0)){
		printf("Per favore digita ok\n");
		goto check_ok_pizza_plus;
	}
	else if(strcmp(check,"stop")!=0) {
		printf("Operazione annullata\n");
		return;
	}
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call espleta_ordine_pizza_plus(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize espleta_ordine_pizza_plusstatement\n", false);
	}

	// non vi e' reset perche i parametri sono gli stessi
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for espleta_ordine_pizza_plus\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore nell'espletare in carico ordine pizza plus.\n");
	} else {
		printf("Ordine pizza plus espletato correttamente\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void prendi_in_carico_ordine_pizza_plus(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	long long int id_ordine;

	visualizza_ordini_pizza_plus_da_espletare(conn);

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call prendi_in_carico_ordine_pizza_plus(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prendi_in_carico_ordine_pizza_plus statement\n", false);
	}

	//Prepare parameters
	memset(param, 0, sizeof(param));
	
	printf("\nID ordine: ");
	if(scanf("%lld", &id_ordine)<1){
		printf("Errore nell'acquisire indice ordine\n");
		return;
	}
	flush_stdin();

	param[0].buffer_type = MYSQL_TYPE_LONGLONG;
	param[0].buffer = &id_ordine;
	param[0].buffer_length = sizeof(id_ordine);
	

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for prendi_in_carico_ordine_pizza_plus\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore nel prendere in carico ordine pizza plus.\n");
	} else {
		printf("Ordine pizza plus preso in carico correttamente\n");
	}

	mysql_stmt_close(prepared_stmt);

	espleta_ordine_pizza_plus(conn,id_ordine);

}

void run_as_pizzaiolo(MYSQL *conn){
	char options[3] = {'1','2','3'};
	char op;
	
	printf("Passo al ruolo di pizzaiolo...\n");

	if(!parse_config("users/pizzaiolo.json", &conf)) {
		fprintf(stderr, "Unable to load pizzaiolo configuration\n");
		exit(EXIT_FAILURE);
	}

	if(mysql_change_user(conn, conf.db_username, conf.db_password, conf.database)) {
		fprintf(stderr, "mysql_change_user() failed\n");
		exit(EXIT_FAILURE);
	}

	while(true) {
		printf("\033[2J\033[H");
		printf("*** Cosa posso fare per te? ***\n\n");
		printf("1) Prendi in carico ordine pizza\n ");
		printf("2) Prendi in carico ordine pizzaplus");
		printf("3) Quit\n");

		op = multiChoice("Seleziona un opzione", options, 3);

		switch(op) {

			case '1':
				prendi_in_carico_ordine_pizza(conn);
				break;
			case '2':
				prendi_in_carico_ordine_pizza_plus(conn);
				break;
			case '3':
				return;
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

		getchar();
	}
}
