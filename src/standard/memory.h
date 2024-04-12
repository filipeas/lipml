int *iftAllocIntArray(long n) {
    int *v = NULL;

    v = (int *) iftAlloc(n, sizeof(int));
    if (v == NULL)
        iftError("Cannot allocate memory space", "iftAllocIntArray");
    return(v);
}