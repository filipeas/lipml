long iftNormalizationValue(long maxval) {
    long norm_val = 1;
    
    if (maxval < 0)
        iftError("Input value %ld < 0", "iftNormalizationValue", maxval);
    else if (maxval <= 1)
        norm_val = 1;
    else if (maxval <= 255)
        norm_val = 255;
    else if (maxval <= 4095)
        norm_val = 4095;
    else if (maxval <= 65535)
        norm_val = 65535;
    else if (maxval <= 4294967295)
        norm_val = 4294967295;
    else iftError("Invalid maxval number %ld with number of bits > 32. It only supports values within [0, 2ˆn_bits -1], " \
                  "where n_bits in {1, 8, 12, 16, 32}", "iftNormalizationValue", maxval);
    
    return norm_val;
}

void iftError(const char *msg, const char *func, ...) {
    va_list args;
    char    final_msg[4096];
    
    va_start(args, func);
    vsprintf(final_msg, msg, args);
    va_end(args);
    
    fprintf(stderr, "\nError in %s: \n%s\n", func, final_msg);
    fflush(stdout);
    exit(-1);
}

double iftLog(double val, double base) {
    return (log(val) / log(base));
}