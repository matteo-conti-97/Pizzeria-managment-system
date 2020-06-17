insert into dbPizzeria.Ingrediente values('funghi',5,0.5);
insert into dbPizzeria.Ingrediente values('pomodori',0,0.5);
insert into dbPizzeria.Ingrediente values('salsiccia',5,0.5);
insert into dbPizzeria.Ingrediente values('uova',5,0.5);
insert into dbPizzeria.Ingrediente values('prosciutto',5,0.5);
insert into dbPizzeria.Ingrediente values('ananas',5,0.5);
insert into dbPizzeria.Pizza values('margherita',5,4.5);
insert into dbPizzeria.Pizza values('boscaiola',0,6.0);
insert into dbPizzeria.Bevanda values('peroni',0,1.5);
insert into dbPizzeria.Bevanda values('coca-cola',5,1.0);
insert into dbPizzeria.Tavolo values(3,2,null);
insert into dbPizzeria.Tavolo values(4,2,null);
call dbPizzeria.registra_cliente('1234', 'matteo', 'conti', 2);
call dbPizzeria.assegna_tavolo_a_cliente('1234', 3);
call dbPizzeria.aggiungi_impiegato(1, 'asda', 'asda', 'manager', 1);
call dbPizzeria.aggiungi_impiegato(2, 'asda', 'asda', 'cameriere', 2);
call dbPizzeria.aggiungi_impiegato(3, 'asda', 'asda', 'pizzaman', 3);
call dbPizzeria.aggiungi_impiegato(4, 'asda', 'asda', 'barman', 4);
call dbPizzeria.assegna_tavolo_a_cameriere(2, 3);
call dbPizzeria.registra_ordine_pizza(3, 'margherita');
call dbPizzeria.registra_ordine_bevanda(3, 'coca-cola');
call dbPizzeria.registra_ordine_pizza_plus(3, 'margherita', 'funghi', '', '', '', '');


