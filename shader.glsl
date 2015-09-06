// shader.glsl

#version 120       // версия glsl

void main() {
    // получаем координату точки на текстуре
    vec2 p = gl_TexCoord[0].xy;

    // число итераций
    int iterations = 5;
    int i;
    for(i=0; i<iterations; ++i) {
        // увеличим наш квадрат 1х1 в 3 раза
        p = 3.0 * p;

        // если попали в середину, то прекращаем итерации
        if (p.x > 1.0 && p.x < 2.0 &&
            p.y > 1.0 && p.y < 2.0)
             break;

        // снова возвращаемся к квадрату 1x1
        p -= vec2(ivec2(p));
    }

    // определяем оттенок серого по числу итераций
    vec3 color = vec3(float(i) / float(iterations));
    gl_FragColor = vec4(color, 1.0);
}