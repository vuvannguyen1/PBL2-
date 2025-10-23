#include "BookingScreen.h"

BookingScreen::BookingScreen(Font& font) : 
    HomeScreen(font),
    buttons_font("../assets/BEBAS_NEUE_ZSMALL.ttf"), 
    current_step(BookingStep::SELECT_DATE),
    suat_chieu(buttons_font, L"SUẤT CHIẾU", 36),
    ghe_ngoi(buttons_font, L"GHẾ NGỒI", 36),
    food(buttons_font, L"ĐỒ ĂN", 36),
    thanh_toan(buttons_font, L"THANH TOÁN", 36),
    xac_nhan(buttons_font, L"XÁC NHẬN", 36),
    tex("../assets/trangchumau1.jpg"),
    sprite(tex)
{
    // ✅ Setup step buttons (navigation bar) - Centered at top
    float startX = 278.f;  // Center: (1728 - (5*180 + 4*10)) / 2
    float startY = 155.f;
    float buttonWidth = 160.f;
    float buttonHeight = 50.f;
    float spacing = 100;

    for (int i = 0; i < 5; i++) {
        buttons_box[i].setSize({buttonWidth, buttonHeight});
        buttons_box[i].setPosition({startX + i * (buttonWidth + spacing), startY});
        
        // Step 1 is active by default
        if (i == 0) {
            buttons_box[i].setFillColor(Color(52, 62, 209)); // Active color
        } else {
            buttons_box[i].setFillColor(Color(80, 80, 90)); // Inactive color
        }
        
        buttons_box[i].setOutlineThickness(2.f);
        buttons_box[i].setOutlineColor(Color(100, 100, 110));
    }

    // ✅ Position text labels on buttons (centered in each button)
    suat_chieu.setPosition({buttons_box[0].getPosition().x + 18, 
                            buttons_box[0].getPosition().y + 3});
    suat_chieu.setFillColor(Color::White);

    ghe_ngoi.setPosition({buttons_box[1].getPosition().x + 30, 
                         buttons_box[1].getPosition().y + 3});
    ghe_ngoi.setFillColor(Color::White);

    food.setPosition({buttons_box[2].getPosition().x + 46, 
                     buttons_box[2].getPosition().y + 3});
    food.setFillColor(Color::White);

    thanh_toan.setPosition({buttons_box[3].getPosition().x + 10, 
                           buttons_box[3].getPosition().y + 3});
    thanh_toan.setFillColor(Color::White);

    xac_nhan.setPosition({buttons_box[4].getPosition().x + 26, 
                         buttons_box[4].getPosition().y + 3});
    xac_nhan.setFillColor(Color::White);

    // ✅ Setup content container (bên phải poster)
    // Poster sẽ ở vị trí: x=168, y=126 với scale 0.36
    // Poster size gốc ~1000x1500, scaled = ~360x540
    content_area.setSize({982.f, 600.f});  // Container bên cạnh poster
    content_area.setPosition({628.f, 235.f});  // Bắt đầu sau poster (168 + 360 + margin)
    content_area.setFillColor(Color(24, 24, 28));
    content_area.setOutlineThickness(2.f);
    content_area.setOutlineColor(Color(60, 60, 70));
}

void BookingScreen::draw(RenderWindow& window) {
    HomeScreen::draw(window);

    // ✅ Draw poster first (from DetailScreen) - giữ nguyên vị trí
    window.draw(sprite);

    // ✅ Draw content area background (container bên cạnh)
    window.draw(content_area);

    // ✅ Draw content based on current step
    drawStepContent(window);

    // ✅ Draw step buttons (navigation bar)
    for (int i = 0; i < 5; i++) 
        window.draw(buttons_box[i]);

    // ✅ Draw button labels
    window.draw(suat_chieu);
    window.draw(ghe_ngoi);
    window.draw(food);
    window.draw(thanh_toan);
    window.draw(xac_nhan);
}

void BookingScreen::loadFromDetail(const DetailScreen& detail) {
    tex = detail.getPosterTexture(); // copy texture
    sprite.setTexture(tex, true); // ✅ true để reset texture rect, giữ chi tiết
    sprite.setScale({0.3f, 0.3f}); // ✅ Giữ scale như ở DetailScreen
    sprite.setPosition({128.f, 235.f}); // ✅ Giữ nguyên vị trí như DetailScreen (trừ margin top cho buttons)
}

void BookingScreen::handleEvent(const RenderWindow& window, const Vector2f& mousePos, bool mousePressed) {
    if (!mousePressed) return;

    // ✅ Check which step button was clicked
    for (int i = 0; i < 5; i++) {
        if (buttons_box[i].getGlobalBounds().contains(mousePos)) {
            // Update current step
            current_step = static_cast<BookingStep>(i);
            
            // Update button colors
            for (int j = 0; j < 5; j++) {
                if (j == i) {
                    buttons_box[j].setFillColor(Color(52, 62, 209)); // Active
                } else {
                    buttons_box[j].setFillColor(Color(80, 80, 90)); // Inactive
                }
            }
            break;
        }
    }
}

void BookingScreen::update(Vector2f mousePos, bool mousePressed, AppState& state) {
    // ✅ Gọi HomeScreen::update để các nút CineXine, Đặt vé, Đăng nhập hoạt động
    HomeScreen::update(mousePos, mousePressed, state);
    
    // TODO: Update content based on current_step
}

void BookingScreen::drawStepContent(RenderWindow& window) {
    Font contentFont("../assets/quicksand_medium.ttf");
    
    // Position inside content area
    float contentX = content_area.getPosition().x + 30.f;
    float contentY = content_area.getPosition().y + 30.f;
    
    switch (current_step) {
        case BookingStep::SELECT_DATE: {
            Text stepTitle(buttons_font, L"CHỌN SUẤT CHIẾU & NGÀY", 32);
            stepTitle.setPosition({contentX, contentY});
            stepTitle.setFillColor(Color::White);
            window.draw(stepTitle);
            
            Text stepDesc(contentFont, L"Vui lòng chọn ngày và giờ chiếu phù hợp", 20);
            stepDesc.setPosition({contentX, contentY + 50});
            stepDesc.setFillColor(Color(200, 200, 200));
            window.draw(stepDesc);
            
            // TODO: Add date/time selection UI
            break;
        }
        
        case BookingStep::SELECT_SEAT: {
            Text stepTitle(buttons_font, L"CHỌN GHẾ NGỒI", 32);
            stepTitle.setPosition({contentX, contentY});
            stepTitle.setFillColor(Color::White);
            window.draw(stepTitle);
            
            Text stepDesc(contentFont, L"Chọn ghế bạn muốn đặt", 20);
            stepDesc.setPosition({contentX, contentY + 50});
            stepDesc.setFillColor(Color(200, 200, 200));
            window.draw(stepDesc);
            
            // TODO: Add seat selection grid
            break;
        }
        
        case BookingStep::SELECT_SNACK: {
            Text stepTitle(buttons_font, L"CHỌN ĐỒ ĂN & NƯỚC UỐNG", 32);
            stepTitle.setPosition({contentX, contentY});
            stepTitle.setFillColor(Color::White);
            window.draw(stepTitle);
            
            Text stepDesc(contentFont, L"Thêm bắp rang bơ, nước ngọt...", 20);
            stepDesc.setPosition({contentX, contentY + 50});
            stepDesc.setFillColor(Color(200, 200, 200));
            window.draw(stepDesc);
            
            // TODO: Add food selection UI
            break;
        }
        
        case BookingStep::PAYMENT: {
            Text stepTitle(buttons_font, L"THANH TOÁN", 32);
            stepTitle.setPosition({contentX, contentY});
            stepTitle.setFillColor(Color::White);
            window.draw(stepTitle);
            
            Text stepDesc(contentFont, L"Chọn phương thức thanh toán", 20);
            stepDesc.setPosition({contentX, contentY + 50});
            stepDesc.setFillColor(Color(200, 200, 200));
            window.draw(stepDesc);
            
            // TODO: Add payment methods
            break;
        }
        
        case BookingStep::CONFIRM: {
            Text stepTitle(buttons_font, L"XÁC NHẬN ĐẶT VÉ", 32);
            stepTitle.setPosition({contentX, contentY});
            stepTitle.setFillColor(Color::White);
            window.draw(stepTitle);
            
            Text stepDesc(contentFont, L"Kiểm tra lại thông tin đặt vé", 20);
            stepDesc.setPosition({contentX, contentY + 50});
            stepDesc.setFillColor(Color(200, 200, 200));
            window.draw(stepDesc);
            
            // TODO: Add booking summary
            break;
        }
    }
}