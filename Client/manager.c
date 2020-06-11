#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "defines.h"

static void registra_cliente(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param1[4];
	MYSQL_BIND param2[2];
	char cf[16];
	char nome[45];
	char cognome[45];
	int commensali;
	int tavolo;

	//Registrazione cliente
	if(!setup_prepared_stmt(&prepared_stmt, "registra_cliente(?,?,?,?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize registra_cliente statement\n", false);
	}

	// Prepare parameters
	memset(param1, 0, sizeof(param1));
	memset(param2, 0, sizeof(param2));

	printf("Inserire CF cliente:\n");
	getInput(16,cf,false);
	printf("Inserire nome cliente:\n");
	getInput(45,nome,false);
	printf("Inserire cognome cliente:\n");
	getInput(45,cognome,false);
	printf("Inserire numero commensali:\n");
	if(scanf("%d",&commensali)<1){
		printf("Errore inserimento numero commensali\n");
		return;
	}

	param1[0].buffer_type = MYSQL_TYPE_STRING;
	param1[0].buffer = cf;
	param1[0].buffer_length = sizeof(cf);

	//For table assignment
	param2[0].buffer_type = MYSQL_TYPE_STRING;
	param2[0].buffer = cf;
	param2[0].buffer_length = sizeof(cf);

	param1[1].buffer_type = MYSQL_TYPE_STRING;
	param1[1].buffer = nome;
	param1[1].buffer_length = sizeof(nome);

	param1[2].buffer_type = MYSQL_TYPE_STRING;
	param1[2].buffer = cognome;
	param1[2].buffer_length = sizeof(cognome);

	param1[3].buffer_type = MYSQL_TYPE_LONG;
	param1[3].buffer = &commensali;
	param1[3].buffer_length = sizeof(commensali);
	
	
	if (mysql_stmt_bind_param(prepared_stmt, param1) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for registra_cliente\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not run register client\n", true);
	} else printf("Cliente registrato correttamente\n");

	mysql_stmt_close(prepared_stmt);


	//Visualizzazione tavoli
	if(!setup_prepared_stmt(&prepared_stmt, "visualizza_tavoli()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_tavoli statement\n", false);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_tavoli\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\n Lista tavoli");
	mysql_stmt_close(prepared_stmt);


	//Assegnazione tavolo

	//Registrazione cliente
	if(!setup_prepared_stmt(&prepared_stmt, "assegna_tavolo_a_cliente(?,?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize assegna_tavolo_a_cliente\n", false);
	}

	// Prepare parameters
	printf("Inserire tavolo:\n");
	if(scanf("%d",&tavolo)<1){
		printf("Errore inserimento tavolo\n");
		return;
	}

	param2[1].buffer_type = MYSQL_TYPE_LONG;
	param2[1].buffer = &tavolo;
	param2[1].buffer_length = sizeof(tavolo);
	
	
	if (mysql_stmt_bind_param(prepared_stmt, param1) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for assegna_tavolo_a_cliente\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not assign table\n", true);
	} else printf("Tavolo assegnato correttamente\n");

	mysql_stmt_close(prepared_stmt);
}

static void stampa_scontrino(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	int tavolo;

	if(!setup_prepared_stmt(&prepared_stmt, "stampa_scontrino(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize stampa_scontrino\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	printf("Inserire tavolo:\n");
	if(scanf("%d",&tavolo)<1){
		printf("Errore inserimento tavolo\n");
		return;
	}

	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &tavolo;
	param[0].buffer_length = sizeof(tavolo);
	
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for stampa_scontrino\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve stampa_scontrino\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nLista dei tavoli associati");
	mysql_stmt_close(prepared_stmt);
}

static void visualizza_entrate_giorno(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	MYSQL_TIME data;

	if(!setup_prepared_stmt(&prepared_stmt, "visualizza_entrate_giorno(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_entrate_giorno\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	printf("Inserire anno:\n");
	if(scanf("%d",&data.year)<1){
		printf("Errore inserimento anno\n");
		return;
	}

	printf("Inserire mese:\n");
	if(scanf("%d",&data.month)<1){
		printf("Errore inserimento mese\n");
		return;
	}

	printf("Inserire giorno:\n");
	if(scanf("%d",&data.day)<1){
		printf("Errore inserimento giorno\n");
		return;
	}

	param[0].buffer_type = MYSQL_TYPE_DATE;
	param[0].buffer = &data;
	param[0].buffer_length = sizeof(data);
	
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for visualizza_entrate_giorno\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_entrate_giorno\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nEntrate:");
	mysql_stmt_close(prepared_stmt);
}

static void visualizza_entrate_mese(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	MYSQL_TIME data;
	data.day=00;

	if(!setup_prepared_stmt(&prepared_stmt, "visualizza_entrate_mese(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_entrate_mese\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	printf("Inserire anno:\n");
	if(scanf("%d",&data.year)<1){
		printf("Errore inserimento anno\n");
		return;
	}

	printf("Inserire mese:\n");
	if(scanf("%d",&data.month)<1){
		printf("Errore inserimento mese\n");
		return;
	}


	param[0].buffer_type = MYSQL_TYPE_DATE;
	param[0].buffer = &data;
	param[0].buffer_length = sizeof(data);
	
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for visualizza_entrate_mese\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_entrate_mese\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nEntrate:");
	mysql_stmt_close(prepared_stmt);
}

static void aumenta_scorte_pizza(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];
	char pizza[45];
	int scorte;

	if(!setup_prepared_stmt(&prepared_stmt, "aumenta_scorte_pizza(?,?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize aumenta_scorte_pizza\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	printf("Inserire pizza\n");
	getInput(45,pizza,false);
	printf("Inserire quantità:\n");
	if(scanf("%d",&scorte)<1){
		printf("Errore inserimento quantità\n");
		return;
	}

	param[0].buffer_type = MYSQL_TYPE_STRING;
	param[0].buffer = pizza;
	param[0].buffer_length = sizeof(pizza);
	param[1].buffer_type = MYSQL_TYPE_LONG;
	param[1].buffer = &scorte;
	param[1].buffer_length = sizeof(scorte);
	
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for aumenta_scorte_pizza\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve refill pizza\n", true);
	}else printf("Scorte aumentate correttamente\n");

	mysql_stmt_close(prepared_stmt);
}

static void aumenta_scorte_bevanda(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];
	char bevanda[45];
	int scorte;

	if(!setup_prepared_stmt(&prepared_stmt, "aumenta_scorte_bevanda(?,?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize aumenta_scorte_bevanda\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	printf("Inserire bevanda\n");
	getInput(45,bevanda,false);
	printf("Inserire quantità:\n");
	if(scanf("%d",&scorte)<1){
		printf("Errore inserimento quantità\n");
		return;
	}

	param[0].buffer_type = MYSQL_TYPE_STRING;
	param[0].buffer = bevanda;
	param[0].buffer_length = sizeof(bevanda);
	param[1].buffer_type = MYSQL_TYPE_LONG;
	param[1].buffer = &scorte;
	param[1].buffer_length = sizeof(scorte);
	
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for aumenta_scorte_bevanda\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve refill bevanda\n", true);
	}else printf("Scorte aumentate correttamente\n");
	
	mysql_stmt_close(prepared_stmt);
}

static void aumenta_scorte_ingrediente(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];
	char ingrediente[45];
	int scorte;

	if(!setup_prepared_stmt(&prepared_stmt, "aumenta_scorte_ingrediente(?,?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize aumenta_scorte_ingrediente\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	printf("Inserire ingrediente\n");
	getInput(45,ingrediente,false);
	printf("Inserire quantità:\n");
	if(scanf("%d",&scorte)<1){
		printf("Errore inserimento quantità\n");
		return;
	}

	param[0].buffer_type = MYSQL_TYPE_STRING;
	param[0].buffer = ingrediente;
	param[0].buffer_length = sizeof(ingrediente);
	param[1].buffer_type = MYSQL_TYPE_LONG;
	param[1].buffer = &scorte;
	param[1].buffer_length = sizeof(scorte);
	
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for aumenta_scorte_ingrediente\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve refill ingrediente\n", true);
	}else printf("Scorte aumentate correttamente\n");
	
	mysql_stmt_close(prepared_stmt);
}

static void aumenta_scorte_tutti_prodotti(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	int scorte;

	if(!setup_prepared_stmt(&prepared_stmt, "aumenta_scorte_tutti_prodotti(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize aumenta_scorte_tutti_prodotti\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	printf("Inserire quantità:\n");
	if(scanf("%d",&scorte)<1){
		printf("Errore inserimento quantità\n");
		return;
	}

	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &scorte;
	param[0].buffer_length = sizeof(scorte);
	
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for aumenta_scorte_tutti_prodotti\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve refill tutti_prodotti\n", true);
	}else printf("Scorte aumentate correttamente\n");
	
	mysql_stmt_close(prepared_stmt);
}

static void aumenta_scorte_prodotto(MYSQL *conn){
	char options[6] = {'1','2','3','4','5'};
	char op;

	while(true) {
		printf("\033[2J\033[H");
		printf("*** Cosa posso fare per te? ***\n\n");
		printf("1) Aumenta scorte pizza\n ");
		printf("2) Aumenta scorte bevanda\n");
		printf("3) Aumenta scorte ingrediene\n");
		printf("4) Aumenta scorte di tutti i prodotti\n");
		printf("5) Quit\n");

		op = multiChoice("Seleziona un opzione", options, 5);

		switch(op) {

			case '1':
				aumenta_scorte_pizza(conn);
				break;
			case '2':
				aumenta_scorte_bevanda(conn);
				break;
			case '3':
				aumenta_scorte_ingrediente(conn);
				break;
			case '4':
				aumenta_scorte_tutti_prodotti(conn);
				break;	
			case '5':
				return;
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

		getchar();
	}
}

static void aggiungi_pizza(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	char pizza[45];

	if(!setup_prepared_stmt(&prepared_stmt, "aggiungi_pizza(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize aggiungi_pizza\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	printf("Inserire pizza\n");
	getInput(45,pizza,false);

	param[0].buffer_type = MYSQL_TYPE_STRING;
	param[0].buffer = pizza;
	param[0].buffer_length = sizeof(pizza);
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for aggiungi_pizza\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not add pizza\n", true);
	}else printf("Pizza aggiunta correttamente\n");

	mysql_stmt_close(prepared_stmt);
}

static void aggiungi_bevanda(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	char bevanda[45];

	if(!setup_prepared_stmt(&prepared_stmt, "aggiungi_bevanda(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize aggiungi_bevanda\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	printf("Inserire bevanda\n");
	getInput(45,bevanda,false);

	param[0].buffer_type = MYSQL_TYPE_STRING;
	param[0].buffer = bevanda;
	param[0].buffer_length = sizeof(bevanda);
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for aggiungi_bevanda\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not add bevanda\n", true);
	}else printf("Bevanda aggiunta correttamente\n");

	mysql_stmt_close(prepared_stmt);
}

static void aggiungi_ingrediente(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	char ingrediente[45];

	if(!setup_prepared_stmt(&prepared_stmt, "aggiungi_ingrediente(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize aggiungi_ingrediente\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	printf("Inserire ingrediente\n");
	getInput(45,ingrediente,false);

	param[0].buffer_type = MYSQL_TYPE_STRING;
	param[0].buffer = ingrediente;
	param[0].buffer_length = sizeof(ingrediente);
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for aggiungi_ingrediente\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not add ingrediente\n", true);
	}else printf("Ingrediente aggiunta correttamente\n");

	mysql_stmt_close(prepared_stmt);
}

static void aggiungi_prodotto(MYSQL *conn){
	char options[5] = {'1','2','3','4'};
	char op;

	while(true) {
		printf("\033[2J\033[H");
		printf("*** Cosa posso fare per te? ***\n\n");
		printf("1) Aggiungi pizza\n ");
		printf("2) Aggiungi bevanda\n");
		printf("3) Aggiungi ingrediente\n");
		printf("4) Quit\n");

		op = multiChoice("Seleziona un opzione", options, 4);

		switch(op) {

			case '1':
				aggiungi_pizza(conn);
				break;
			case '2':
				aggiungi_bevanda(conn);
				break;
			case '3':
				aggiungi_ingrediente(conn);
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

static void rimuovi_pizza(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	char pizza[45];

	if(!setup_prepared_stmt(&prepared_stmt, "rimuovi_pizza(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize rimuovi_pizza\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	printf("Inserire pizza\n");
	getInput(45,pizza,false);

	param[0].buffer_type = MYSQL_TYPE_STRING;
	param[0].buffer = pizza;
	param[0].buffer_length = sizeof(pizza);
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for rimuovi_pizza\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not remove pizza\n", true);
	}else printf("Pizza rimossa correttamente\n");

	mysql_stmt_close(prepared_stmt);
}

static void rimuovi_bevanda(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	char bevanda[45];

	if(!setup_prepared_stmt(&prepared_stmt, "rimuovi_bevanda(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize rimuovi_bevanda\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	printf("Inserire bevanda\n");
	getInput(45,bevanda,false);

	param[0].buffer_type = MYSQL_TYPE_STRING;
	param[0].buffer = bevanda;
	param[0].buffer_length = sizeof(bevanda);
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for rimuovi_bevanda\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not remove bevanda\n", true);
	}else printf("Bevanda rimossa correttamente\n");

	mysql_stmt_close(prepared_stmt);
}

static void rimuovi_ingrediente(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	char ingrediente[45];

	if(!setup_prepared_stmt(&prepared_stmt, "rimuovi_ingrediente(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize rimuovi_ingrediente\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	printf("Inserire ingrediente\n");
	getInput(45,ingrediente,false);

	param[0].buffer_type = MYSQL_TYPE_STRING;
	param[0].buffer = ingrediente;
	param[0].buffer_length = sizeof(ingrediente);
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for rimuovi_ingrediente\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not remove ingrediente\n", true);
	}else printf("Ingrediente rimuovi correttamente\n");

	mysql_stmt_close(prepared_stmt);
}

static void rimuovi_prodotto(MYSQL *conn){
	char options[5] = {'1','2','3','4'};
	char op;

	while(true) {
		printf("\033[2J\033[H");
		printf("*** Cosa posso fare per te? ***\n\n");
		printf("1) Rimuovi pizza\n ");
		printf("2) Rimuovi bevanda\n");
		printf("3) Rimuovi ingrediente\n");
		printf("4) Quit\n");

		op = multiChoice("Seleziona un opzione", options, 4);

		switch(op) {

			case '1':
				rimuovi_pizza(conn);
				break;
			case '2':
				rimuovi_bevanda(conn);
				break;
			case '3':
				rimuovi_ingrediente(conn);
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

static void visualizza_prodotti(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;

	//Pizza
	if(!setup_prepared_stmt(&prepared_stmt, "visualizza_menu_pizze()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_menu_pizze statement\n", false);
	}
	
	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_menu_pizze\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\n Lista pizze");
	mysql_stmt_close(prepared_stmt);

	//Pizzaplus

	if(!setup_prepared_stmt(&prepared_stmt, "visualizza_menu_ingredienti()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_menu_ingredienti statement\n", false);
	}
	
	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_menu_ingredienti\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\n Lista ingredienti");
	mysql_stmt_close(prepared_stmt);

	//Bevanda

	if(!setup_prepared_stmt(&prepared_stmt, "visualizza_menu_bevande()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_menu_bevande statement\n", false);
	}
	
	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_menu_bevande\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\n Lista bevande");
	mysql_stmt_close(prepared_stmt);
}

static void gestisci_prodotti(MYSQL *conn){
	char options[6] = {'1','2','3','4','5'};
	char op;

	while(true) {
		printf("\033[2J\033[H");
		printf("*** Cosa posso fare per te? ***\n\n");
		printf("1) Visualizza prodotti\n ");
		printf("2) Aumenta scorte prodotto\n");
		printf("3) Aggiungi prodotto\n");
		printf("4) Rimuovi prodotto\n");
		printf("5) Quit\n");

		op = multiChoice("Seleziona un opzione", options, 5);

		switch(op) {

			case '1':
				visualizza_prodotti(conn);
				break;
			case '2':
				aumenta_scorte_prodotto(conn);
				break;
			case '3':
				aggiungi_prodotto(conn);
				break;
			case '4':
				rimuovi_prodotto(conn);
				break;	
			case '5':
				return;
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

		getchar();
	}
}

static void aggiungi_tavolo(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	int tavolo;

	if(!setup_prepared_stmt(&prepared_stmt, "aggiungi_tavolo(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize aggiungi_tavolo\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	printf("Inserire numero tavolo\n");
	if(scanf("%d",&tavolo)<1){
		printf("Errore nell'acquisire numero tavolo\n");
		return;
	}

	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &tavolo;
	param[0].buffer_length = sizeof(tavolo);
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for aggiungi_tavolo\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not add tavolo\n", true);
	}else printf("Tavolo aggiunto correttamente\n");

	mysql_stmt_close(prepared_stmt);
}

static void rimuovi_tavolo(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	int tavolo;

	if(!setup_prepared_stmt(&prepared_stmt, "aggiungi_tavolo(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize rimuovi_tavolo\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	printf("Inserire numero tavolo\n");
	if(scanf("%d",&tavolo)<1){
		printf("Errore nell'acquisire numero tavolo\n");
		return;
	}

	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &tavolo;
	param[0].buffer_length = sizeof(tavolo);
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for rimuovi_tavolo\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not remove tavolo\n", true);
	}else printf("Tavolo rimosso correttamente\n");

	mysql_stmt_close(prepared_stmt);
}

static void gestisci_tavoli(MYSQL *conn){
	char options[4] = {'1','2','3'};
	char op;

	while(true) {
		printf("\033[2J\033[H");
		printf("*** Cosa posso fare per te? ***\n\n");
		printf("1) Aggiungi tavolo\n ");
		printf("2) Rimuovi tavolo\n");
		printf("3) Quit\n");

		op = multiChoice("Seleziona un opzione", options, 3);

		switch(op) {

			case '1':
				aggiungi_tavolo(conn);
				break;
			case '2':
				rimuovi_tavolo(conn);
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

static void visualizza_turni_impiegati(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;

	if(!setup_prepared_stmt(&prepared_stmt, "visualizza_turni_impiegati()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_turni_impiegati\n", false);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_turni_impiegati\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nTurni impiegati:");
	mysql_stmt_close(prepared_stmt);
}

static void visualizza_turni_tavoli(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;

	if(!setup_prepared_stmt(&prepared_stmt, "visualizza_turni_tavoli()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_turni_tavoli\n", false);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_turni_tavoli\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nTurni tavoli:");
	mysql_stmt_close(prepared_stmt);
}

static void assegna_turno_a_impiegato(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[4];
	int impiegato;
	char str_giorno[9];
	int giorno;
	MYSQL_TIME ora_inizio;
	MYSQL_TIME ora_fine;
	ora_inizio.second=00;
	ora_fine.second=00;

	//Visualizza turni
	if(!setup_prepared_stmt(&prepared_stmt, "visualizza_turni()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_turni\n", false);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_turni\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nTurni:");
	mysql_stmt_close(prepared_stmt);

	//Visualizza impiegati
	if(!setup_prepared_stmt(&prepared_stmt, "visualizza_impiegati()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize visualizza_impiegati\n", false);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve visualizza_impiegati\n", true);
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nImpiegati:");
	mysql_stmt_close(prepared_stmt);
	


	if(!setup_prepared_stmt(&prepared_stmt, "assegna_turno_a_impiegato(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize assegna_turno_a_impiegato\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	printf("Inserisci matricola impiegato\n");
	if(scanf("%d",&impiegato)<1){
		printf("Errore acquisizione impiegato\n");
	}
	
	//AGGIUNGERE CONTROLLI SEGNO E GRANDEZZA
	printf("Inserire ora inizio turno:\n");
	if(scanf("%d",&ora_inizio.hour)<1){
		printf("Errore inserimento ora inizio turno\n");
		return;
	}

	printf("Inserire minuto inizio turno:\n");
	if(scanf("%d",&ora_inizio.minute)<1){
		printf("Errore inserimento minuto inizio turno\n");
		return;
	}

	printf("Inserire ora fine turno:\n");
	if(scanf("%d",&ora_fine.hour)<1){
		printf("Errore inserimento ora fine turno\n");
		return;
	}

	printf("Inserire minuto fine turno:\n");
	if(scanf("%d",&ora_fine.minute)<1){
		printf("Errore inserimento minuto fine turno\n");
		return;
	}


	giorno:
		printf("Inserire giorno senza accenti:\n");
		if(scanf("%s",str_giorno)<1){
			printf("Errore inserimento giorno\n");
			return;
		}

		str_lower(str_giorno);

		if(strcmp(str_giorno,"domenica")==0) giorno=0;
		else if(strcmp(str_giorno,"lunedi")==0) giorno=1;
		else if(strcmp(str_giorno,"martedi")==0) giorno=2;
		else if(strcmp(str_giorno,"mercoledi")==0) giorno=3;
		else if(strcmp(str_giorno,"giovedi")==0) giorno=4;
		else if(strcmp(str_giorno,"venerdi")==0) giorno=5;
		else if(strcmp(str_giorno,"sabato")==0) giorno=6;
		else {
			printf("Digitare il giorno correttamente\n");
			goto giorno;
		}



	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &impiegato;
	param[0].buffer_length = sizeof(impiegato);

	param[1].buffer_type = MYSQL_TYPE_TIME;
	param[1].buffer = &ora_inizio;
	param[1].buffer_length = sizeof(ora_inizio);

	param[2].buffer_type = MYSQL_TYPE_TIME;
	param[2].buffer = &ora_fine;
	param[2].buffer_length = sizeof(ora_fine);

	param[3].buffer_type = MYSQL_TYPE_LONG;
	param[3].buffer = &giorno;
	param[3].buffer_length = sizeof(giorno);
	
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for assegna_turno_a_impiegato\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not retrieve assegna_turno_a_impiegato\n", true);
	}else printf("Turno assegnato correttamente\n");
	mysql_stmt_close(prepared_stmt);

}

static void gestisci_turni(MYSQL *conn){
	char options[4] = {'1','2','3'};
	char op;

	while(true) {
		printf("\033[2J\033[H");
		printf("*** Cosa posso fare per te? ***\n\n");
		printf("1) Visualizza turni impiegati\n");
		printf("2) Visualizza turni tavoli\n");
		printf("3) Assegna turno a impiegato\n");
		printf("4) Rimuovi turno a impiegato\n");
		printf("5) Assegna turno a tavolo\n");
		printf("6) Rimuovi turno a tavolo\n");
		printf("7) Aggiungi turno\n ");
		printf("8) Rimuovi turno\n");
		printf("9) Quit\n");

		op = multiChoice("Seleziona un opzione", options, 3);

		switch(op) {

			case '1':
				visualizza_turni_impiegati(conn);
				break;
			case '2':
				visualizza_turni_tavoli(conn);
				break;
			case '3':
				assegna_turno_a_impiegato(conn);
				break;
			case '4':
				rimuovi_turno_a_impiegato(conn);
				break;
			case '5':
				assegna_turno_a_tavolo(conn);
				break;
			case '6':
				rimuovi_turno_a_tavolo(conn);
				break;
			case '7':
				aggiungi_turno(conn);
				break;
			case '8':
				rimuovi_turno(conn);
				break;
			case '9':
				return;
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

		getchar();
	}
}




void run_as_manager(MYSQL *conn){
	char options[10] = {'1','2','3','4','5','6','7','8','9'};
	char op;
	
	printf("Passo al ruolo di manager...\n");

	if(!parse_config("users/manager.json", &conf)) {
		fprintf(stderr, "Unable to load manager configuration\n");
		exit(EXIT_FAILURE);
	}

	if(mysql_change_user(conn, conf.db_username, conf.db_password, conf.database)) {
		fprintf(stderr, "mysql_change_user() failed\n");
		exit(EXIT_FAILURE);
	}

	while(true) {
		printf("\033[2J\033[H");
		printf("*** Cosa posso fare per te? ***\n\n");
		printf("1) Registra cliente\n ");
		printf("2) Stampa scontrino\n");
		printf("3) Gestisci prodotti\n");
		printf("4) Gestisci tavoli\n");
		printf("5) Gestisci impiegati\n");
		printf("6) Gestisci turni\n");
		printf("7) Visualizza entrate giornaliere\n");
		printf("8) Visualizza entrate mensili\n");
		printf("9) Quit\n");

		op = multiChoice("Seleziona un opzione", options, 9);

		switch(op) {

			case '1':
				registra_cliente(conn);
				break;
			case '2':
				stampa_scontrino(conn);
				break;
			case '3':
				gestisci_prodotti(conn);
				break;
			case '4':
				gestisci_tavoli(conn);
				break;	
			case '5':
				gestisci_impiegati(conn);
				break;
			case '6':
				gestisci_turni(conn);
				break;
			case '7':
				visualizza_entrate_giorno(conn);
				break;
			case '8':
				visualizza_entrate_mese(conn);
				break;	
			case '9':
				return;
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

		getchar();
	}
}