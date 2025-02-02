#include "../app.h"
#include "../text.h"
#include "../shapes.h"
// Or using the single-header file:
// #include "../SlimApp.h"

typedef struct { u8 left, right, up, down; } Nav;
Nav nav_keys, nav_keys_pressed;

void drawKeyboard() {
    // Get the window content from the app and clear it all to black:
    PixelGrid *canvas = &app->window_content;
    fillPixelGrid(canvas, Color(Black));

    Rect rect;

    // Draw the keyboard contour:
    rect.min.x = 220;
    rect.max.x = 450;
    rect.min.y = 180;
    rect.max.y = 280;
    drawRect(canvas, Color(White), &rect);

    // Draw the 'A' key:
    rect.min.x = 256;
    rect.max.x = 276;
    rect.min.y = 216;
    rect.max.y = 236;
    fillRect(canvas, Color(nav_keys_pressed.left ? White : Grey), &rect);
    drawText(canvas, Color(nav_keys_pressed.left ? Grey : White), "A", rect.min.x + 5, rect.min.y + 5);

    // Draw the 'S' key:
    rect.min.x += 22;
    rect.max.x += 22;
    fillRect(canvas, Color(nav_keys_pressed.down ? White : Grey), &rect);
    drawText(canvas, Color(nav_keys_pressed.down ? Grey : White), "S", rect.min.x + 5, rect.min.y + 5);

    // Draw the 'D' key:
    rect.min.x += 22;
    rect.max.x += 22;
    fillRect(canvas, Color(nav_keys_pressed.right ? White : Grey), &rect);
    drawText(canvas, Color(nav_keys_pressed.right ? Grey : White), "D", rect.min.x + 5, rect.min.y + 5);

    // Draw the 'W' key:
    rect.min.x -= 28;
    rect.max.x -= 28;
    rect.min.y -= 22;
    rect.max.y -= 22;
    fillRect(canvas, Color(nav_keys_pressed.up ? White : Grey), &rect);
    drawText(canvas, Color(nav_keys_pressed.up ? Grey : White), "W", rect.min.x + 5, rect.min.y + 5);

    // Draw the left Ctrl key:
    rect.min.x = 222;
    rect.max.x = 250;
    rect.min.y = 260;
    rect.max.y = 278;
    fillRect(canvas, Color(app->controls.is_pressed.ctrl ? Blue : Cyan), &rect);

    // Draw the left Alt key:
    rect.min.x += 30;
    rect.max.x += 30;
    fillRect(canvas, Color(app->controls.is_pressed.alt ? Red : Magenta), &rect);

    // Draw the left Shift key:
    rect.min.x -= 30;
    rect.max.x -= 15;
    rect.min.y -= 20;
    rect.max.y -= 20;
    fillRect(canvas, Color(app->controls.is_pressed.shift ? Green : Yellow), &rect);

    // Draw the right Ctrl key:
    rect.min.x = 420;
    rect.max.x = 448;
    rect.min.y = 260;
    rect.max.y = 278;
    fillRect(canvas, Color(app->controls.is_pressed.ctrl ? Blue : Cyan), &rect);

    // Draw the right Alt key:
    rect.min.x -= 30;
    rect.max.x -= 30;
    fillRect(canvas, Color(app->controls.is_pressed.alt ? Red : Magenta), &rect);

    // Draw the right Shift key:
    rect.min.x += 15;
    rect.max.x += 30;
    rect.min.y -= 20;
    rect.max.y -= 20;
    fillRect(canvas, Color(app->controls.is_pressed.shift ? Green : Yellow), &rect);

    // Draw the Space key:
    rect.min.x = 280;
    rect.max.x = 390;
    rect.min.y = 260;
    rect.max.y = 278;
    fillRect(canvas,
             Color(app->controls.is_pressed.space ?
                   White : Grey), &rect);
}
void keyChanged(u8 key, bool pressed) {
    // Capture changes to custom-bound keys and store their state:
    if (key == nav_keys.left)  nav_keys_pressed.left  = pressed;
    if (key == nav_keys.right) nav_keys_pressed.right = pressed;
    if (key == nav_keys.up)    nav_keys_pressed.up    = pressed;
    if (key == nav_keys.down)  nav_keys_pressed.down  = pressed;
}

void initApp(Defaults *defaults) {
    // Tell the app how to draw the window content,
    // and what to do when the keyboard state changes:
    app->on.windowRedraw = drawKeyboard;
    app->on.keyChanged   = keyChanged;

    // Custom key-binding:
    nav_keys.up    = 'W';
    nav_keys.left  = 'A';
    nav_keys.down  = 'S';
    nav_keys.right = 'D';

    // Initialize key states:
    nav_keys_pressed.left  = false;
    nav_keys_pressed.right = false;
    nav_keys_pressed.up    = false;
    nav_keys_pressed.down  = false;
}

