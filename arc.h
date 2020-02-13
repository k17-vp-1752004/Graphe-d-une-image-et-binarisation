struct Arc {
    int target;                 // target vertex
    double capacite;        // capacite du Arc
    double flot;            //  flot actuel dans Arc
    int inverse;            // indice d'inverse Arc dans adj liste

    Arc(int target, double capacite, int inverse) {
        this->target = target;
        this->capacite = capacite;z
        this->flot = 0;
        this->inverse = inverse;
    }
};