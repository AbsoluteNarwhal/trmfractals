#version 330 core
in vec2 fragCoord;
out vec4 fragColor;

uniform vec2 u_center;
uniform float u_zoom;
uniform int u_maxIter;

void main() {
    // Map fragment to complex plane
    vec2 c = fragCoord / u_zoom + u_center;

    vec2 z = vec2(0.0);
    int iter = 0;

    for (int i = 0; i < u_maxIter; i++) {
        if (dot(z, z) > 4.0) break; // |z|^2 > 4.0 is divergent (outside the set)
        z = vec2(z.x*z.x - z.y*z.y, 2.0*z.x*z.y) + c; // z = z^2 + c
        iter++;
    }

    // |z|^2 <= 4.0 (inside the set)
    if (dot(z, z) <= 4.0) {
        fragColor = vec4(0.0, 0.0, 0.0, 1.0);
        return;
    }

    // Diverges faster = different colour
    // I came up with these colours using an advanced technique called picking random numbers and seeing if they look good
    float t = float(iter) / float(u_maxIter);
    fragColor = vec4(
        0.5 + 0.5 * cos(6.28318 * (t * 3.0 + 0.0)),
        0.5 + 0.5 * cos(6.28318 * (t * 3.0 + 0.33)),
        0.5 + 0.5 * cos(6.28318 * (t * 3.0 + 0.67)),
        1.0
    );
}