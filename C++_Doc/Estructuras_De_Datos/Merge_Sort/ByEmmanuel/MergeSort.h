//
// Created by Jesus Emmanuel Garcia on 9/24/25.
//
inline ListaDobleLigada* Merge(ListaDobleLigada* izq, ListaDobleLigada* der){
    ListaDobleLigada* resultado = new ListaDobleLigada();
    int i = 0, j = 0;
    Nodo* aux_izq = izq->head;
    Nodo* aux_der = der->head;

    while (i < izq->size() && j < der->size()){
        if (aux_izq->get_tipoDato_actual() <= aux_der->get_tipoDato_actual()){
            resultado->push_bottom(aux_izq);
            aux_izq = aux_izq->siguiente;
            i++;
        } else {
            resultado->push_bottom(aux_der);
            aux_der = aux_der->siguiente;
            j++;
        }
    }

    while (i < izq->size()){
        resultado->push_bottom(aux_izq);
        aux_izq = aux_izq->siguiente;
        i++;
    }
    while (j < der->size()){
        resultado->push_bottom(aux_der);
        aux_der = aux_der->siguiente;
        j++;
    }

    return resultado;

}

// primero esta
inline ListaDobleLigada* MergeSort(ListaDobleLigada* lista){
    int tamaño = lista->size();
    // esto garantiza que efectivamente hay elemento en la lista y no se sobrepasara de la misma
    // por ende no es necesario hacer un while(tmp)
    if (tamaño <= 1)return lista;
    int medio = tamaño / 2;
    int i = 0;


    ListaDobleLigada* list_tmp_1 = new ListaDobleLigada();
    Nodo* tmp = lista->head;
    for (i = 0; i < medio; i++){
    list_tmp_1->push_bottom(tmp);
        if (tmp->siguiente){
            tmp = tmp->siguiente;
        }
    }

    ListaDobleLigada* list_tmp_2 = new ListaDobleLigada();
    while (i < tamaño){
    list_tmp_2->push_bottom(tmp);
        if (tmp->siguiente){
            tmp = tmp->siguiente;
        }
        i++;
    }

    ListaDobleLigada* izq = MergeSort(list_tmp_1);
    ListaDobleLigada* der = MergeSort(list_tmp_2);

    return Merge(izq, der);
}

