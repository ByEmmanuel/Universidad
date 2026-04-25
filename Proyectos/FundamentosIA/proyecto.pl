% ============================================================
%  SISTEMA EXPERTO: CLASIFICACION DE DINOSAURIOS
%  Materia: Fundamentos de IA — CUCEI, UDG
%  Autor  : Jesus Emmanuel
% ============================================================
%
%  BASE DE CONOCIMIENTO
%  Hechos estructurados por predicado:
%
%    grupo(Nombre, Grupo)
%       Grupo ∈ {terapodo, sauropodo, ornitopodo,
%                marginocefalo, tireoforo}
%
%    dieta(Nombre, Dieta)
%       Dieta ∈ {carnivoro, herbivoro, omnivoro}
%
%    periodo(Nombre, Periodo)
%       Periodo ∈ {triasico, jurasico, cretacico}
%
%    locomocion(Nombre, Modo)
%       Modo ∈ {bipedo, cuadrupedo, anfibio}
%
%    tamanio(Nombre, Tamanio)
%       Tamanio ∈ {pequenio, mediano, grande, gigante}
%
%    caracteristica_especial(Nombre, Rasgo)
%       Rasgo: átomo descriptivo libre
%
% ============================================================

% ------------------------------------------------------------
% 1. Tyrannosaurus rex
% ------------------------------------------------------------
grupo(tyrannosaurus_rex, terapodo).
dieta(tyrannosaurus_rex, carnivoro).
periodo(tyrannosaurus_rex, cretacico).
locomocion(tyrannosaurus_rex, bipedo).
tamanio(tyrannosaurus_rex, gigante).
caracteristica_especial(tyrannosaurus_rex, brazos_vestigiales).
caracteristica_especial(tyrannosaurus_rex, mordida_mas_poderosa_entre_terrestres).

% ------------------------------------------------------------
% 2. Triceratops
% ------------------------------------------------------------
grupo(triceratops, marginocefalo).
dieta(triceratops, herbivoro).
periodo(triceratops, cretacico).
locomocion(triceratops, cuadrupedo).
tamanio(triceratops, grande).
caracteristica_especial(triceratops, tres_cuernos_faciales).
caracteristica_especial(triceratops, gola_osea_protectora).

% ------------------------------------------------------------
% 3. Brachiosaurus
% ------------------------------------------------------------
grupo(brachiosaurus, sauropodo).
dieta(brachiosaurus, herbivoro).
periodo(brachiosaurus, jurasico).
locomocion(brachiosaurus, cuadrupedo).
tamanio(brachiosaurus, gigante).
caracteristica_especial(brachiosaurus, cuello_extremadamente_largo).
caracteristica_especial(brachiosaurus, extremidades_anteriores_mas_largas).

% ------------------------------------------------------------
% 4. Velociraptor
% ------------------------------------------------------------
grupo(velociraptor, terapodo).
dieta(velociraptor, carnivoro).
periodo(velociraptor, cretacico).
locomocion(velociraptor, bipedo).
tamanio(velociraptor, pequenio).
caracteristica_especial(velociraptor, garra_en_hoz_en_segundo_dedo).
caracteristica_especial(velociraptor, probable_cobertura_de_plumas).

% ------------------------------------------------------------
% 5. Stegosaurus
% ------------------------------------------------------------
grupo(stegosaurus, tireoforo).
dieta(stegosaurus, herbivoro).
periodo(stegosaurus, jurasico).
locomocion(stegosaurus, cuadrupedo).
tamanio(stegosaurus, grande).
caracteristica_especial(stegosaurus, placas_dorsales_oseas).
caracteristica_especial(stegosaurus, thagomizer_en_cola).

% ------------------------------------------------------------
% 6. Diplodocus
% ------------------------------------------------------------
grupo(diplodocus, sauropodo).
dieta(diplodocus, herbivoro).
periodo(diplodocus, jurasico).
locomocion(diplodocus, cuadrupedo).
tamanio(diplodocus, gigante).
caracteristica_especial(diplodocus, cola_muy_larga_tipo_latigo).
caracteristica_especial(diplodocus, dientes_en_forma_de_lapiz).

% ------------------------------------------------------------
% 7. Allosaurus
% ------------------------------------------------------------
grupo(allosaurus, terapodo).
dieta(allosaurus, carnivoro).
periodo(allosaurus, jurasico).
locomocion(allosaurus, bipedo).
tamanio(allosaurus, grande).
caracteristica_especial(allosaurus, crestas_supraorbitales).
caracteristica_especial(allosaurus, depredador_apical_del_jurasico).

% ------------------------------------------------------------
% 8. Ankylosaurus
% ------------------------------------------------------------
grupo(ankylosaurus, tireoforo).
dieta(ankylosaurus, herbivoro).
periodo(ankylosaurus, cretacico).
locomocion(ankylosaurus, cuadrupedo).
tamanio(ankylosaurus, grande).
caracteristica_especial(ankylosaurus, armadura_osteodermica_completa).
caracteristica_especial(ankylosaurus, maza_osea_en_cola).

% ------------------------------------------------------------
% 9. Parasaurolophus
% ------------------------------------------------------------
grupo(parasaurolophus, ornitopodo).
dieta(parasaurolophus, herbivoro).
periodo(parasaurolophus, cretacico).
locomocion(parasaurolophus, bipedo).
tamanio(parasaurolophus, grande).
caracteristica_especial(parasaurolophus, cresta_tubular_hueca_en_cabeza).
caracteristica_especial(parasaurolophus, podia_caminar_en_cuatro_patas).

% ------------------------------------------------------------
% 10. Spinosaurus
% ------------------------------------------------------------
grupo(spinosaurus, terapodo).
dieta(spinosaurus, carnivoro).
periodo(spinosaurus, cretacico).
locomocion(spinosaurus, bipedo).
tamanio(spinosaurus, gigante).
caracteristica_especial(spinosaurus, vela_o_joroba_dorsal).
caracteristica_especial(spinosaurus, dieta_piscivora_predominante).

% ------------------------------------------------------------
% 11. Iguanodon
% ------------------------------------------------------------
grupo(iguanodon, ornitopodo).
dieta(iguanodon, herbivoro).
periodo(iguanodon, cretacico).
locomocion(iguanodon, bipedo).
tamanio(iguanodon, grande).
caracteristica_especial(iguanodon, pulgar_en_forma_de_espiga).
caracteristica_especial(iguanodon, uno_de_los_primeros_dinosaurios_descritos).

% ------------------------------------------------------------
% 12. Pachycephalosaurus
% ------------------------------------------------------------
grupo(pachycephalosaurus, marginocefalo).
dieta(pachycephalosaurus, herbivoro).
periodo(pachycephalosaurus, cretacico).
locomocion(pachycephalosaurus, bipedo).
tamanio(pachycephalosaurus, mediano).
caracteristica_especial(pachycephalosaurus, cupula_craneal_osea_gruesa).
caracteristica_especial(pachycephalosaurus, posible_comportamiento_de_embestida).

% ------------------------------------------------------------
% 13. Baryonyx
% ------------------------------------------------------------
grupo(baryonyx, terapodo).
dieta(baryonyx, carnivoro).
periodo(baryonyx, cretacico).
locomocion(baryonyx, bipedo).
tamanio(baryonyx, grande).
caracteristica_especial(baryonyx, garras_grandes_en_manos).
caracteristica_especial(baryonyx, hocico_largo_similar_a_cocodrilo).

% ------------------------------------------------------------
% 14. Carnotaurus
% ------------------------------------------------------------
grupo(carnotaurus, terapodo).
dieta(carnotaurus, carnivoro).
periodo(carnotaurus, cretacico).
locomocion(carnotaurus, bipedo).
tamanio(carnotaurus, grande).
caracteristica_especial(carnotaurus, cuernos_sobre_los_ojos).
caracteristica_especial(carnotaurus, piel_con_osteodermos_descritos).

% ------------------------------------------------------------
% 15. Archaeopteryx
% ------------------------------------------------------------
grupo(archaeopteryx, terapodo).
dieta(archaeopteryx, carnivoro).
periodo(archaeopteryx, jurasico).
locomocion(archaeopteryx, bipedo).
tamanio(archaeopteryx, pequenio).
caracteristica_especial(archaeopteryx, plumas_verdaderas).
caracteristica_especial(archaeopteryx, transicion_dinosaurio_ave).

% ------------------------------------------------------------
% 16. Pteranodon  (Pterosaurio — grupo externo, incluido por interes)
% ------------------------------------------------------------
grupo(pteranodon, terapodo).          % pterosaurio arcosaurio, no dinosaurio estricto
dieta(pteranodon, carnivoro).
periodo(pteranodon, cretacico).
locomocion(pteranodon, bipedo).
tamanio(pteranodon, mediano).
caracteristica_especial(pteranodon, cresta_craneal_larga).
caracteristica_especial(pteranodon, vuelo_activo_membranoso).

% ------------------------------------------------------------
% 17. Argentinosaurus
% ------------------------------------------------------------
grupo(argentinosaurus, sauropodo).
dieta(argentinosaurus, herbivoro).
periodo(argentinosaurus, cretacico).
locomocion(argentinosaurus, cuadrupedo).
tamanio(argentinosaurus, gigante).
caracteristica_especial(argentinosaurus, uno_de_los_animales_terrestres_mas_grandes).
caracteristica_especial(argentinosaurus, vertebras_dorsales_de_gran_tamanio).

% ------------------------------------------------------------
% 18. Therizinosaurus
% ------------------------------------------------------------
grupo(therizinosaurus, terapodo).
dieta(therizinosaurus, herbivoro).
periodo(therizinosaurus, cretacico).
locomocion(therizinosaurus, bipedo).
tamanio(therizinosaurus, gigante).
caracteristica_especial(therizinosaurus, garras_frontales_mas_largas_conocidas).
caracteristica_especial(therizinosaurus, terapodo_herbivoro).

% ------------------------------------------------------------
% 19. Gallimimus
% ------------------------------------------------------------
grupo(gallimimus, terapodo).
dieta(gallimimus, omnivoro).
periodo(gallimimus, cretacico).
locomocion(gallimimus, bipedo).
tamanio(gallimimus, mediano).
caracteristica_especial(gallimimus, sin_dientes_pico_similar_a_ave).
caracteristica_especial(gallimimus, velocidad_de_carrera_alta).

% ------------------------------------------------------------
% 20. Oviraptor
% ------------------------------------------------------------
grupo(oviraptor, terapodo).
dieta(oviraptor, omnivoro).
periodo(oviraptor, cretacico).
locomocion(oviraptor, bipedo).
tamanio(oviraptor, pequenio).
caracteristica_especial(oviraptor, cresta_osea_en_cabeza).
caracteristica_especial(oviraptor, cuidado_parental_de_huevos_confirmado).

% ------------------------------------------------------------
% 21. Dilophosaurus
% ------------------------------------------------------------
grupo(dilophosaurus, terapodo).
dieta(dilophosaurus, carnivoro).
periodo(dilophosaurus, jurasico).
locomocion(dilophosaurus, bipedo).
tamanio(dilophosaurus, mediano).
caracteristica_especial(dilophosaurus, dos_crestas_paralelas_en_craneo).
caracteristica_especial(dilophosaurus, uno_de_los_primeros_grandes_terapodos).

% ------------------------------------------------------------
% 22. Ceratosaurus
% ------------------------------------------------------------
grupo(ceratosaurus, terapodo).
dieta(ceratosaurus, carnivoro).
periodo(ceratosaurus, jurasico).
locomocion(ceratosaurus, bipedo).
tamanio(ceratosaurus, grande).
caracteristica_especial(ceratosaurus, cuerno_nasal_prominente).
caracteristica_especial(ceratosaurus, osteodermos_a_lo_largo_del_dorso).

% ------------------------------------------------------------
% 23. Muttaburrasaurus
% ------------------------------------------------------------
grupo(muttaburrasaurus, ornitopodo).
dieta(muttaburrasaurus, herbivoro).
periodo(muttaburrasaurus, cretacico).
locomocion(muttaburrasaurus, bipedo).
tamanio(muttaburrasaurus, grande).
caracteristica_especial(muttaburrasaurus, protuberancia_nasal_inflada).
caracteristica_especial(muttaburrasaurus, denticion_para_cortar_vegetacion_dura).

% ------------------------------------------------------------
% 24. Kentrosaurus
% ------------------------------------------------------------
grupo(kentrosaurus, tireoforo).
dieta(kentrosaurus, herbivoro).
periodo(kentrosaurus, jurasico).
locomocion(kentrosaurus, cuadrupedo).
tamanio(kentrosaurus, mediano).
caracteristica_especial(kentrosaurus, placas_y_puas_a_lo_largo_del_dorso).
caracteristica_especial(kentrosaurus, puas_en_hombros_y_cola).

% ------------------------------------------------------------
% 25. Sauroposeidon
% ------------------------------------------------------------
grupo(sauroposeidon, sauropodo).
dieta(sauroposeidon, herbivoro).
periodo(sauroposeidon, cretacico).
locomocion(sauroposeidon, cuadrupedo).
tamanio(sauroposeidon, gigante).
caracteristica_especial(sauroposeidon, posiblemente_el_dinosaurio_mas_alto).
caracteristica_especial(sauroposeidon, vertebras_cervicales_neumatizadas).

% ------------------------------------------------------------
% 26. Maiasaura
% ------------------------------------------------------------
grupo(maiasaura, ornitopodo).
dieta(maiasaura, herbivoro).
periodo(maiasaura, cretacico).
locomocion(maiasaura, bipedo).
tamanio(maiasaura, grande).
caracteristica_especial(maiasaura, evidencia_de_cuidado_parental_en_nidos).
caracteristica_especial(maiasaura, vivian_en_grandes_manadas).

% ------------------------------------------------------------
% 27. Styracosaurus
% ------------------------------------------------------------
grupo(styracosaurus, marginocefalo).
dieta(styracosaurus, herbivoro).
periodo(styracosaurus, cretacico).
locomocion(styracosaurus, cuadrupedo).
tamanio(styracosaurus, grande).
caracteristica_especial(styracosaurus, gola_con_multiples_cuernos_largos).
caracteristica_especial(styracosaurus, cuerno_nasal_largo).

% ------------------------------------------------------------
% 28. Carcharodontosaurus
% ------------------------------------------------------------
grupo(carcharodontosaurus, terapodo).
dieta(carcharodontosaurus, carnivoro).
periodo(carcharodontosaurus, cretacico).
locomocion(carcharodontosaurus, bipedo).
tamanio(carcharodontosaurus, gigante).
caracteristica_especial(carcharodontosaurus, dientes_serrados_como_tiburon).
caracteristica_especial(carcharodontosaurus, craneo_mas_largo_que_t_rex).

% ------------------------------------------------------------
% 29. Giganotosaurus
% ------------------------------------------------------------
grupo(giganotosaurus, terapodo).
dieta(giganotosaurus, carnivoro).
periodo(giganotosaurus, cretacico).
locomocion(giganotosaurus, bipedo).
tamanio(giganotosaurus, gigante).
caracteristica_especial(giganotosaurus, depredador_apical_sudamericano).
caracteristica_especial(giganotosaurus, cerebro_en_forma_de_platano).

% ------------------------------------------------------------
% 30. Protoceratops
% ------------------------------------------------------------
grupo(protoceratops, marginocefalo).
dieta(protoceratops, herbivoro).
periodo(protoceratops, cretacico).
locomocion(protoceratops, cuadrupedo).
tamanio(protoceratops, pequenio).
caracteristica_especial(protoceratops, gola_osea_sin_cuernos).
caracteristica_especial(protoceratops, nidos_y_huevos_fosiles_encontrados).


% ============================================================
%  REGLAS DE INFERENCIA
% ============================================================

% --- Regla 1: Depredador ---
% Un dinosaurio es depredador si es carnivoro y bipedo
depredador(X) :-
    dieta(X, carnivoro),
    locomocion(X, bipedo).

% --- Regla 2: Megadepredador ---
% Depredador de gran tamanio (grande o gigante)
megadepredador(X) :-
    depredador(X),
    ( tamanio(X, grande) ; tamanio(X, gigante) ).

% --- Regla 3: Dinosaurio blindado ---
% Tireoforo con locomocion cuadrupeda
blindado(X) :-
    grupo(X, tireoforo),
    locomocion(X, cuadrupedo).

% --- Regla 4: Cuernado ---
% Marginocefalo con cuernos (regla sobre caracteristica especial)
cuernado(X) :-
    grupo(X, marginocefalo),
    caracteristica_especial(X, Rasgo),
    sub_atom(Rasgo, _, _, _, cuerno).

% --- Regla 5: Sauropodo gigante ---
sauropodo_gigante(X) :-
    grupo(X, sauropodo),
    tamanio(X, gigante).

% --- Regla 6: Dinosaurio cretacico herbivoro ---
cretacico_herbivoro(X) :-
    periodo(X, cretacico),
    dieta(X, herbivoro).

% --- Regla 7: Posible ancestro de aves ---
% Terapodo con plumas en sus caracteristicas
ancestro_de_aves(X) :-
    grupo(X, terapodo),
    caracteristica_especial(X, Rasgo),
    ( sub_atom(Rasgo, _, _, _, pluma) ; sub_atom(Rasgo, _, _, _, ave) ).

% --- Regla 8: Clasificacion general de tamanos ---
% Pequenio: longitud < ~3 m   → tamanio(pequenio)
% Mediano : ~3-7 m            → tamanio(mediano)
% Grande  : ~7-15 m           → tamanio(grande)
% Gigante : > 15 m            → tamanio(gigante)

% --- Regla 9: Compartir nicho ecologico ---
% Dos dinosaurios comparten nicho si tienen mismo periodo, misma dieta
% y misma locomocion (posible competencia)
mismo_nicho(X, Y) :-
    X \= Y,
    periodo(X, P), periodo(Y, P),
    dieta(X, D),  dieta(Y, D),
    locomocion(X, L), locomocion(Y, L).

% --- Regla 10: Dinosaurio con defensa activa ---
% Tireoforo O marginocefalo (ambos grupos tienen estructuras defensivas)
defensa_activa(X) :-
    ( grupo(X, tireoforo) ; grupo(X, marginocefalo) ).


% ============================================================
%  MOTOR DE CONSULTA — interfaz de usuario por texto
% ============================================================

% Listar todos los dinosaurios registrados
todos_los_dinosaurios :-
    findall(D, grupo(D, _), Ds),
    sort(Ds, Unicos),
    forall(member(D, Unicos), (write(D), nl)).

% Mostrar ficha completa de un dinosaurio
ficha(Dinosaurio) :-
    ( grupo(Dinosaurio, G) ->
        format("~n=== ~w ===~n", [Dinosaurio]),
        format("  Grupo        : ~w~n", [G]),
        ( dieta(Dinosaurio, D)      -> format("  Dieta        : ~w~n", [D]) ; true ),
        ( periodo(Dinosaurio, P)    -> format("  Periodo      : ~w~n", [P]) ; true ),
        ( locomocion(Dinosaurio, L) -> format("  Locomocion   : ~w~n", [L]) ; true ),
        ( tamanio(Dinosaurio, T)    -> format("  Tamanio      : ~w~n", [T]) ; true ),
        findall(R, caracteristica_especial(Dinosaurio, R), Rs),
        format("  Rasgos esp.  : ~w~n", [Rs])
    ;
        format("Dinosaurio '~w' no encontrado en la base de conocimiento.~n", [Dinosaurio])
    ).

% Consultar todos los megadepredadores
listar_megadepredadores :-
    findall(X, megadepredador(X), L),
    sort(L, S),
    write('Megadepredadores: '), write(S), nl.

% Consultar todos los sauropodos gigantes
listar_sauropodos_gigantes :-
    findall(X, sauropodo_gigante(X), L),
    sort(L, S),
    write('Sauropodos gigantes: '), write(S), nl.

% Consultar posibles ancestros de aves
listar_ancestros_aves :-
    findall(X, ancestro_de_aves(X), L),
    sort(L, S),
    write('Posibles ancestros de aves: '), write(S), nl.

% Buscar dinosaurios por dieta
por_dieta(Dieta) :-
    findall(X, dieta(X, Dieta), L),
    sort(L, S),
    format("Dinosaurios ~w: ~w~n", [Dieta, S]).

% Buscar dinosaurios por periodo
por_periodo(Periodo) :-
    findall(X, periodo(X, Periodo), L),
    sort(L, S),
    format("Dinosaurios del ~w: ~w~n", [Periodo, S]).

% Buscar dinosaurios por grupo
por_grupo(Grupo) :-
    findall(X, grupo(X, Grupo), L),
    sort(L, S),
    format("Grupo ~w: ~w~n", [Grupo, S]).

