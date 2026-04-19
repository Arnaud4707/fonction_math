// kernel.cl
__kernel void fill_background(__global unsigned int* pixels, int width, int height, unsigned int color) {
    // Chaque thread du GPU récupère ses coordonnées uniques
    int x = get_global_id(0);
    int y = get_global_id(1);

    if (x < width && y < height) {
        pixels[y * width + x] = color;
    }
}