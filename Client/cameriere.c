#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "defines.h"

static void visualizza_info_tavoli_associati(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];


	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_info_tavoli_associati(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_info_tavoli_associati statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &conf.username;
	param[0].buffer_length = sizeof(conf.username);
	
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for visualizza_ordini_pizza_da_espletare\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_info_tavoli_associati\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nLista dei tavoli associati");
	mysql_stmt_close(prepared_stmt);
}

static void registra_ordine_pizza(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];
	char pizza[45];
	int tavolo;


	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_menu_pizze()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_menu_pizze statement\n", false);
	}


	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_menu_pizze\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\n Menu' pizze");
	mysql_stmt_close(prepared_stmt);

	// Prepare parameters
	memset(param, 0, sizeof(param));

	printf("Inserisci il tavolo:\n");

	if(scanf("%d",&tavolo)<1){
		printf("Errore nell'acquisire il tavolo\n");
		return;
	}

	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &tavolo;
	param[0].buffer_length = sizeof(tavolo);

	printf("Inserisci la pizza:\n");

	getInput(45,pizza,false);

	param[1].buffer_type = MYSQL_TYPE_STRING;
	param[1].buffer = pizza;
	param[1].buffer_length = sizeof(pizza);
	
	if(!setup_prepared_stmt(&prepared_stmt, "call registra_ordine_pizza(?,?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize registra_ordine_pizza statement\n", false);
	}
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters registra_ordine_pizza\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve registra_ordine_pizza\n", true);
	}else printf("Ordine pizza registrato correttamente\n");

	mysql_stmt_close(prepared_stmt);
}

static void registra_ordine_bevanda(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];
	char bevanda[45];
	int tavolo;


	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_menu_bevande()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_menu_bevande statement\n", false);
	}


	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_menu_bevande\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\n Menu' bevande");
	mysql_stmt_close(prepared_stmt);

	// Prepare parameters
	memset(param, 0, sizeof(param));

	printf("Inserisci il tavolo:\n");

	if(scanf("%d",&tavolo)<1){
		printf("Errore nell'acquisire il tavolo\n");
		return;
	}

	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &tavolo;
	param[0].buffer_length = sizeof(tavolo);

	printf("Inserisci la bevanda:\n");

	getInput(45,bevanda,false);

	param[1].buffer_type = MYSQL_TYPE_STRING;
	param[1].buffer = bevanda;
	param[1].buffer_length = sizeof(bevanda);
	
	if(!setup_prepared_stmt(&prepared_stmt, "call registra_ordine_bevanda(?,?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize registra_ordine_bevanda statement\n", false);
	}
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters registra_ordine_bevanda\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve registra_ordine_bevanda\n", true);
	}else printf("Ordine bevanda registrato correttamente\n");

	mysql_stmt_close(prepared_stmt);
}

static void registra_ordine_pizza_plus(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[7];
	char pizza[45];
	char ing[5][45];
	int tavolo;


	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_menu_pizze()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_menu_pizze statement\n", false);
	}


	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_menu_pizze\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\n Menu' pizze");
	mysql_stmt_close(prepared_stmt);

	// Prepare parameters
	memset(param, 0, sizeof(param));

	printf("Inserisci il tavolo:\n");

	if(scanf("%d",&tavolo)<1){
		printf("Errore nell'acquisire il tavolo\n");
		return;
	}

	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &tavolo;
	param[0].buffer_length = sizeof(tavolo);

	printf("Inserisci la pizza da usare come base:\n");

	getInput(45,pizza,false);

	param[1].buffer_type = MYSQL_TYPE_STRING;
	param[1].buffer = pizza;
	param[1].buffer_length = sizeof(pizza);

	int i=0;
	bool stop=true;
	for(i=0;i<5;i++){
		if(!stop){
			printf("Inserire ingrediente %d oppure digitare stop per terminare inserimento\n",i+1);
			getInput(45,ing[i],false);
			if(strcmp(ing[i],"stop")==0){
				strcpy(ing[i],"");
				stop=false;
			}
		}else strcpy(ing[i],"");
			param[i+2].buffer_type = MYSQL_TYPE_STRING;
			param[i+2].buffer = ing[i];
			param[i+2].buffer_length = sizeof(ing[i]);
	}

	if(!setup_prepared_stmt(&prepared_stmt, "call registra_ordine_pizza_plus(?,?,?,?,?,?,?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize registra_ordine_pizza_plus statement\n", false);
	}
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters registra_ordine_pizza_plus\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve registra_ordine_pizza_plus\n", true);
	}else printf("Ordine pizza plus registrato correttamente\n");

	mysql_stmt_close(prepared_stmt);
}

static void registra_ordine(MYSQL *conn) {
	char options[7] = {'1','2','3','4'};
	char op;

	while(true) {
		printf("\033[2J\033[H");
		printf("*** Cosa posso fare per te? ***\n\n");
		printf("1) Registra ordine pizza");
		printf("2) Registra ordine pizza plus");
		printf("3) Registra ordine bevanda");
		printf("4) Quit\n");

		op = multiChoice("Seleziona un opzione", options, 4);

		switch(op) {

			case '1':
				registra_ordine_pizza(conn);
				break;
			case '2':
				registra_ordine_pizza_plus(conn);
				break;
			case '3':
				registra_ordine_bevanda(conn);
				break;
			case '4':
				return;
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

		getchar();
	}	
}

static void visualizza_ordini_espletati(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;

	//Pizza
	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_ordini_espletati_pizza()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_ordini_espletati_pizza statement\n", false);
	}
	

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_ordini_espletati_pizza\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nLista ordini pizza espletati");
	mysql_stmt_close(prepared_stmt);

	//Pizzaplus

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_ordini_espletati_pizza_plus()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_ordini_espletati_pizza_plus statement\n", false);
	}
	
	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_ordini_espletati_pizza_plus\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nLista ordini pizza plus espletati");
	mysql_stmt_close(prepared_stmt);

	//Bevanda

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_ordini_espletati_bevanda()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_ordini_espletati_bevanda statement\n", false);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_ordini_espletati_bevanda\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nLista ordini bevanda espletati");
	mysql_stmt_close(prepared_stmt);
}

static void consegna_ordine_pizza(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	long long int id_ordine;

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_ordini_espletati_pizza()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_ordini_espletati_pizza statement\n", false);
	}


	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_ordini_espletati_pizza\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nLista delle pizze espletate");
	mysql_stmt_close(prepared_stmt);


	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call consegna_ordine_pizza(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize consegna_ordine_pizza statement\n", false);
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
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for consegna_ordine_pizza\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore nel consegnare  ordine pizza.\n");
	} else {
		printf("Ordine pizza consegnato correttamente\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void consegna_ordine_bevanda(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	long long int id_ordine;

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_ordini_espletati_bevanda()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_ordini_espletati_bevanda statement\n", false);
	}


	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_ordini_espletati_bevanda\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nLista delle bevande espletate");
	mysql_stmt_close(prepared_stmt);


	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call consegna_ordine_bevanda(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize consegna_ordine_bevanda statement\n", false);
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
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for consegna_ordine_bevanda\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore nel consegnare ordine bevanda.\n");
	} else {
		printf("Ordine bevanda consegnato correttamente\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void consegna_ordine_pizza_plus(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	long long int id_ordine;

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_ordini_espletati_pizza_plus()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_ordini_espletati_pizza_plus statement\n", false);
	}


	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_ordini_espletati_pizza_plus\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nLista delle pizze plus espletate");
	mysql_stmt_close(prepared_stmt);


	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call consegna_ordine_pizza_plus(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize consegna_ordine_pizza_plus statement\n", false);
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
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for consegnaordine_pizza_plus\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore nel consegnare  ordine pizza plus.\n");
	} else {
		printf("Ordine pizza plus consegnato correttamente\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void consegna_ordine(MYSQL *conn) {
	char options[7] = {'1','2','3','4'};
	char op;

	while(true) {
		printf("\033[2J\033[H");
		printf("*** Cosa posso fare per te? ***\n\n");
		printf("1) Consegna ordine pizza");
		printf("2) Consegna ordine pizza plus");
		printf("3) Consegna ordine bevanda");
		printf("4) Quit\n");

		op = multiChoice("Seleziona un opzione", options, 4);

		switch(op) {

			case '1':
				consegna_ordine_pizza(conn);
				break;
			case '2':
				consegna_ordine_pizza_plus(conn);
				break;
			case '3':
				consegna_ordine_bevanda(conn);
				break;
			case '4':
				return;
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

		getchar();
	}	
}

static void visualizza_menu(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;

	//Pizza
	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_menu_pizze()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_menu_pizze statement\n", false);
	}
	
	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_menu_pizze\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\n Menu' pizze");
	mysql_stmt_close(prepared_stmt);

	//Pizzaplus

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_menu_ingredienti()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_menu_ingredienti statement\n", false);
	}
	
	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_menu_ingredienti\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\n Menu' ingredienti");
	mysql_stmt_close(prepared_stmt);

	//Bevanda

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_menu_bevande()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_menu_bevande statement\n", false);
	}
	
	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_menu_bevande\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\n Menu' bevande");
	mysql_stmt_close(prepared_stmt);
}

void run_as_cameriere(MYSQL *conn){
	char options[7] = {'1','2','3','4','5','6'};
	char op;
	
	printf("Passo al ruolo di cameriere...\n");

	if(!parse_config("users/cameriere.json", &conf)) {
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
		printf("2) Registra ordine");
		printf("3) Visualizza ordini espletati");
		printf("4) Consegna ordine");
		printf("5) Visualizza menu'");
		printf("6) Quit\n");

		op = multiChoice("Seleziona un opzione", options, 6);

		switch(op) {

			case '1':
				visualizza_info_tavoli_associati(conn);
				break;
			case '2':
				registra_ordine(conn);
				break;
			case '3':
				visualizza_ordini_espletati(conn);
				break;
			case '4':
				consegna_ordine(conn);
				break;
			case '5':
				visualizza_menu(conn);
				break;
			case '6':
				return;
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

		getchar();
	}
}
