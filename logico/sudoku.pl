:- use_module(library(clpfd)).

sudoku(Linhas) :-
    length(Linhas, 9),
    maplist(same_length(Linhas), Linhas),
    append(Linhas, TodosElementos),
    TodosElementos ins 1..9,
    maplist(all_different, Linhas),
    transpose(Linhas, Colunas),
    maplist(all_different, Colunas),
    Linhas = [A,B,C, D,E,F, G,H,I],
    verifica_blocos(A, B, C),
    verifica_blocos(D, E, F),
    verifica_blocos(G, H, I).

verifica_blocos([], [], []).
verifica_blocos([N1,N2,N3|Cauda1], [N4,N5,N6|Cauda2], [N7,N8,N9|Cauda3]) :-
    all_different([N1,N2,N3,N4,N5,N6,N7,N8,N9]),
    verifica_blocos(Cauda1, Cauda2, Cauda3).

instancia(1, [
    [5,3,_, _,7,_, _,_,_],
    [6,_,_, 1,9,5, _,_,_],
    [_,9,8, _,_,_, _,6,_],
    [8,_,_, _,6,_, _,_,3],
    [4,_,_, 8,_,3, _,_,1],
    [7,_,_, _,2,_, _,_,6],
    [_,6,_, _,_,_, 2,8,_],
    [_,_,_, 4,1,9, _,_,5],
    [_,_,_, _,8,_, _,7,9]
]).

instancia(2, [
    [_,_,_, _,_,_, _,_,_],
    [_,_,_, _,_,3, _,8,5],
    [_,_,1, _,2,_, _,_,_],
    [_,_,_, 5,_,7, _,_,_],
    [_,_,4, _,_,_, 1,_,_],
    [_,9,_, _,_,_, _,_,_],
    [5,_,_, _,_,_, _,7,3],
    [_,_,2, _,1,_, _,_,_],
    [_,_,_, _,4,_, _,_,9]
]).

resolver(ID) :-
    instancia(ID, Tabuleiro),
    sudoku(Tabuleiro),
    maplist(label, Tabuleiro),
    format('~n--- Solucao da Instancia ~w ---~n', [ID]),
    maplist(portray_clause, Tabuleiro).