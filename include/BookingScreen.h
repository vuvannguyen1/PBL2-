#pragma once
#include <SFML/Graphics.hpp>
#include "HomeScreen.h"
#include "DetailScreen.h"

enum class BookingStep {
    SELECT_DATE,
    SELECT_SEAT,
    SELECT_SNACK,
    PAYMENT,
    CONFIRM
};

class BookingScreen : public HomeScreen {
private:
    Font buttons_font;
    BookingStep current_step;
    Text suat_chieu, ghe_ngoi, food, thanh_toan, xac_nhan;
    RectangleShape buttons_box[5];
    Texture tex;
    Sprite sprite;

    RectangleShape content_area;

    // Helper function to draw content based on step
    void drawStepContent(RenderWindow&);
public:
    BookingScreen(Font&);
    void handleEvent(const RenderWindow&, const Vector2f&, bool);
    void update(Vector2f, bool, AppState&); // ✅ Thêm tham số giống HomeScreen
    void draw(RenderWindow&);

    void loadFromDetail(const DetailScreen&);
};
