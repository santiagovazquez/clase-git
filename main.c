struct mapCDT {
	elemType * values; // Arreglo dinámico de valores. La clave es la posición.
	char * occupied; // Arreglo dinámico de ceros y unos para indicar si la posición es vacía.
	size_t dim; // Dimensión del arreglo dinámico de valores.
	size_t elemCount; // Cantidad de elementos
};

mapADT newMap() {
	return calloc(1, sizeof(struct mapCDT));
}
 
void freeMap(mapADT map) {
	free(map->values);
	free(map->occupied);
	free(map);
}
 
void putKeyValue(mapADT map, unsigned int key, elemType value) {
	if(key >= map->dim) {
		map->values = realloc(map->values, (key + 1) * sizeof(elemType));
		map->occupied = realloc(map->occupied, (key + 1) * sizeof(char));
		for(int i = map->dim; i <= key; i++) {
			map->occupied[i] = 0;
		}
		map->dim = key + 1;
	}
	if(!hasKey(map, key)) {
		map->occupied[key] = 1;
		map->elemCount++;
	}
	map->values[key] = value;
}

int getValue(const mapADT map, unsigned int key, elemType * value) {
	if(!hasKey(map, key)) {
		return 0;
	}
	*value = map->values[key];
	return 1;
}

int hasKey(const mapADT map, unsigned int key) {
	return key < map->dim && map->occupied[key] == 1;
}
 
unsigned int * getKeys(const mapADT map, elemType value, int * dim) {
	unsigned int * res = NULL;
	*dim = 0;
	for(int i = 0; i < map->dim; i++) {
		if(map->occupied[i] && compare(map->values[i], value) == 0) {
			if(*dim % BLOQUE == 0) {
				res = realloc(res, (*dim + BLOQUE) * sizeof(unsigned int));
			}
			res[(*dim)++] = i;
		}
	}
	if(*dim > 0) {
		res = realloc(res, *dim * sizeof(unsigned int));
	}
	return res;
}
 
unsigned int size(const mapADT map) {
	return map->elemCount;
}

elemType * values(const mapADT map) {
	if(size(map) == 0) {
		return NULL;
	}
	elemType * res = malloc(size(map) * sizeof(elemType));
	for(int i = 0, k = 0; i < map->dim; i++) {
		if(map->occupied[i]) {
			res[k++] = map->values[i];
		}
	}
	return res;
}

