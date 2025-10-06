// #include "LoginScreen.h"
// using namespace sf;

// // ===== Constructor =====
// LoginScreen::LoginScreen(const Font& font)
//     : overlay({0.f, 0.f}),   // resize trong draw()
//       card({460.f, 360.f}),
//       title(font, L"Đăng nhập", 30),
//       emailBox({360.f, 44.f}),
//       passBox({360.f, 44.f}),
//       btn({360.f, 44.f}),
//       emailPH(font, L"Nhập email hoặc số điện thoại", 18),
//       passPH(font, L"Nhập mật khẩu", 18),
//       btnText(font, L"Tiếp tục", 20),
//       linkForgot(font, L"Quên mật khẩu?", 16),
//       linkCreate(font, L"Tạo tài khoản ngay", 16),
//       closeX(font, L"X", 20),
//       emailDisplay(font, L"", 18),
//       passDisplay(font, L"", 18)
// {
//     // overlay
//     overlay.setFillColor(Color(0, 0, 0, 170));

//     // card
//     card.setFillColor(Color(255, 255, 255, 240));
//     card.setOrigin(card.getSize() / 2.f);

//     // title
//     title.setFillColor(Color::Black);

//     // email
//     emailBox.setFillColor(Color(238, 238, 238));
//     emailPH.setFillColor(Color(100, 100, 100));

//     // password
//     passBox.setFillColor(Color(238, 238, 238));
//     passPH.setFillColor(Color(100, 100, 100));

//     // button
//     btn.setFillColor(Color(100, 149, 237));
//     btnText.setFillColor(Color::White);

//     // links
//     linkForgot.setFillColor(Color(90, 90, 90));
//     linkCreate.setFillColor(Color(36, 95, 180));

//     // close X
//     closeX.setFillColor(Color(90, 90, 90));

//     emailDisplay.setFillColor(Color::Black);
//     passDisplay.setFillColor(Color::Black);
// }

// // ===== Update =====
// bool LoginScreen::update(Vector2f mouse, bool mousePressed, const Event& event) {
//     // click ra ngoài card -> đóng
//     if (mousePressed && !card.getGlobalBounds().contains(mouse))
//         return true;

//     // click vào nút X -> đóng
//     if (mousePressed && closeX.getGlobalBounds().contains(mouse))
//         return true;

//     // chọn ô active
//     if (mousePressed) {
//         emailActive = emailBox.getGlobalBounds().contains(mouse);
//         passActive  = passBox.getGlobalBounds().contains(mouse);
//     }

//     // nhập text realtime
//     if (event.is<Event::TextEntered>()) {
//         char32_t unicode = event.getIf<Event::TextEntered>()->unicode;

//         if (emailActive) {
//             if (unicode == 8) { // backspace
//                 if (!emailInput.empty()) emailInput.pop_back();
//             } else if (unicode >= 32 && unicode <= 126) {
//                 emailInput.push_back((wchar_t)unicode);
//             }
//         }
//         else if (passActive) {
//             if (unicode == 8) {
//                 if (!passInput.empty()) passInput.pop_back();
//             } else if (unicode >= 32 && unicode <= 126) {
//                 passInput.push_back((wchar_t)unicode);
//             }
//         }
//     }

//     return false; // chưa đóng
// }

// // ===== Draw =====
// void LoginScreen::draw(RenderWindow& window) {
//     auto size = window.getSize();
//     overlay.setSize({(float)size.x, (float)size.y});
//     Vector2f center({size.x * 0.5f, size.y * 0.5f});
//     card.setPosition(center);

//     title.setPosition({center.x - 90.f, center.y - 150.f});

//     emailBox.setPosition({center.x - 180.f, center.y - 88.f});
//     emailPH.setPosition({emailBox.getPosition().x + 12.f, emailBox.getPosition().y + 10.f});

//     passBox.setPosition({center.x - 180.f, center.y - 34.f});
//     passPH.setPosition({passBox.getPosition().x + 12.f, passBox.getPosition().y + 10.f});

//     btn.setPosition({center.x - 180.f, center.y + 22.f});
//     btnText.setPosition({btn.getPosition().x + 125.f, btn.getPosition().y + 8.f});

//     linkForgot.setPosition({center.x - 180.f, center.y + 78.f});
//     linkCreate.setPosition({center.x - 180.f, center.y + 104.f});

//     closeX.setPosition({
//         card.getPosition().x + card.getSize().x / 2.f - 28.f,
//         card.getPosition().y - card.getSize().y / 2.f + 8.f
//     });

//     // draw overlay + card
//     window.draw(overlay);
//     window.draw(card);

//     // draw UI
//     window.draw(title);
//     window.draw(emailBox);
//     window.draw(passBox);
//     window.draw(btn);
//     window.draw(btnText);
//     window.draw(linkForgot);
//     window.draw(linkCreate);
//     window.draw(closeX);

//     // hiển thị text hoặc placeholder
//     if (emailInput.empty()) {
//         window.draw(emailPH);
//     } else {
//         emailDisplay.setString(emailInput);
//         emailDisplay.setPosition({emailBox.getPosition().x + 12.f, emailBox.getPosition().y + 10.f});
//         window.draw(emailDisplay);
//     }

//     if (passInput.empty()) {
//         window.draw(passPH);
//     } else {
//         std::wstring stars(passInput.size(), L'*');
//         passDisplay.setString(stars);
//         passDisplay.setPosition({passBox.getPosition().x + 12.f, passBox.getPosition().y + 10.f});
//         window.draw(passDisplay);
//     }
// }

#include "LoginScreen.h"
using namespace sf;

static Text makeText(const Font& font, const String& str, unsigned size) {
    Text t(font, str, size);
    t.setFillColor(Color::Black);
    return t;
}

LoginScreen::LoginScreen(const Font& font, AuthService& authRef)
    : auth(authRef),
      overlay({0.f, 0.f}),
      card({460.f, 380.f}),
      title(font, L"Đăng nhập", 30),
      emailBox({360.f, 44.f}),
      passBox({360.f, 44.f}),
      btn({360.f, 44.f}),
      emailPH(font, L"Nhập email hoặc tài khoản", 18),
      passPH(font, L"Nhập mật khẩu", 18),
      btnText(font, L"Tiếp tục", 20),
      linkForgot(font, L"Quên mật khẩu?", 16),
      linkCreate(font, L"Tạo tài khoản ngay", 16),
      closeX(font, L"X", 20),
      emailDisplay(font, L"", 18),
      passDisplay(font, L"", 18),
      msg(font, L"", 16)
{
    overlay.setFillColor(Color(0, 0, 0, 170));

    card.setFillColor(Color(255, 255, 255, 240));
    card.setOrigin(card.getSize() / 2.f);

    title.setFillColor(Color::Black);

    emailBox.setFillColor(Color(238, 238, 238));
    emailBox.setOutlineThickness(2.f);
    emailBox.setOutlineColor(Color(200,200,200));
    emailPH.setFillColor(Color(100,100,100));

    passBox = emailBox;
    passPH.setFillColor(Color(100,100,100));

    btn.setFillColor(Color(100, 149, 237));
    btnText.setFillColor(Color::White);

    linkForgot.setFillColor(Color(90,90,90));
    linkCreate.setFillColor(Color(36,95,180));
    closeX.setFillColor(Color(90,90,90));

    emailDisplay.setFillColor(Color::Black);
    passDisplay.setFillColor(Color::Black);

    msg.setFillColor(Color(200,60,60)); // mặc định đỏ
}

std::wstring LoginScreen::bullets(std::size_t n) { return std::wstring(n, L'\u2022'); }

bool LoginScreen::update(Vector2f mouse, bool mousePressed, const Event& event) {
    // click ra ngoài card -> đóng
    if (mousePressed && !card.getGlobalBounds().contains(mouse)) return true;

    // click X -> đóng
    if (mousePressed && closeX.getGlobalBounds().contains(mouse)) return true;

    // chọn ô active
    if (mousePressed) {
        emailActive = emailBox.getGlobalBounds().contains(mouse);
        passActive  = passBox.getGlobalBounds().contains(mouse);

        // click Continue
        if (btn.getGlobalBounds().contains(mouse)) {
            // verify
            std::string u(emailInput.begin(), emailInput.end());
            std::string p(passInput.begin(), passInput.end());
            if (auth.verify(u, p)) {
                msg.setFillColor(Color(60,160,90));
                msg.setString(L"Đăng nhập thành công.");
            } else {
                msg.setFillColor(Color(200,60,60));
                msg.setString(L"Sai tài khoản hoặc mật khẩu.");
            }
        }

        // click "Tạo tài khoản ngay" -> nếu chưa tồn tại sẽ đăng ký luôn
        if (linkCreate.getGlobalBounds().contains(mouse)) {
            std::string u(emailInput.begin(), emailInput.end());
            std::string p(passInput.begin(), passInput.end());
            if (u.empty() || p.empty()) {
                msg.setFillColor(Color(200,60,60));
                msg.setString(L"Không được để trống.");
            } else if (!auth.registerUser(u, p)) {
                msg.setFillColor(Color(200,60,60));
                msg.setString(L"Tài khoản đã tồn tại.");
            } else {
                msg.setFillColor(Color(60,160,90));
                msg.setString(L"Đăng ký thành công. Hãy đăng nhập.");
            }
        }
    }

    // phím
    if (event.is<Event::KeyPressed>()) {
        auto code = event.getIf<Event::KeyPressed>()->code;
        if (code == Keyboard::Key::Escape) return true;              // đóng
        if (code == Keyboard::Key::Tab) {                            // chuyển ô
            bool e = emailActive, p = passActive;
            emailActive = !e && !p ? true : !e;
            passActive  = !emailActive;
        } else if (code == Keyboard::Key::Backspace) {               // xóa
            if (emailActive && !emailInput.empty()) emailInput.pop_back();
            else if (passActive && !passInput.empty()) passInput.pop_back();
        } else if (code == Keyboard::Key::Enter) {                   // xác nhận
            std::string u(emailInput.begin(), emailInput.end());
            std::string p(passInput.begin(), passInput.end());
            if (auth.verify(u, p)) {
                msg.setFillColor(Color(60,160,90));
                msg.setString(L"Đăng nhập thành công.");
            } else {
                msg.setFillColor(Color(200,60,60));
                msg.setString(L"Sai tài khoản hoặc mật khẩu.");
            }
        }
    }

    if (event.is<Event::TextEntered>()) {
        char32_t unicode = event.getIf<Event::TextEntered>()->unicode;
        if (unicode >= 32 && unicode <= 126) { // printable ASCII
            if (emailActive && emailInput.size() < 48) emailInput.push_back((wchar_t)unicode);
            else if (passActive && passInput.size() < 48)  passInput.push_back((wchar_t)unicode);
        }
    }

    return false; // không đóng
}

void LoginScreen::draw(RenderWindow& window) {
    auto size = window.getSize();
    overlay.setSize({(float)size.x, (float)size.y});
    Vector2f center({size.x * 0.5f, size.y * 0.5f});
    card.setPosition(center);

    title.setPosition({center.x - 90.f, center.y - 160.f});

    emailBox.setPosition({center.x - 180.f, center.y - 96.f});
    emailPH.setPosition({emailBox.getPosition().x + 12.f, emailBox.getPosition().y + 10.f});

    passBox.setPosition({center.x - 180.f, center.y - 42.f});
    passPH.setPosition({passBox.getPosition().x + 12.f, passBox.getPosition().y + 10.f});

    btn.setPosition({center.x - 180.f, center.y + 14.f});
    btnText.setPosition({btn.getPosition().x + 125.f, btn.getPosition().y + 8.f});

    linkForgot.setPosition({center.x - 180.f, center.y + 70.f});
    linkCreate.setPosition({center.x - 180.f, center.y + 96.f});

    closeX.setPosition({card.getPosition().x + card.getSize().x/2.f - 28.f,
                        card.getPosition().y - card.getSize().y/2.f + 8.f});

    msg.setPosition({center.x - 180.f, center.y + 132.f});

    // vẽ
    window.draw(overlay);
    window.draw(card);

    window.draw(title);
    window.draw(emailBox);
    window.draw(passBox);
    window.draw(btn);
    window.draw(btnText);
    window.draw(linkForgot);
    window.draw(linkCreate);
    window.draw(closeX);
    window.draw(msg);

    // placeholder / text thật
    if (emailInput.empty()) {
        window.draw(emailPH);
    } else {
        emailDisplay.setString(emailInput);
        emailDisplay.setPosition({emailBox.getPosition().x + 12.f, emailBox.getPosition().y + 10.f});
        window.draw(emailDisplay);
    }

    if (passInput.empty()) {
        window.draw(passPH);
    } else {
        passDisplay.setString(bullets(passInput.size()));
        passDisplay.setPosition({passBox.getPosition().x + 12.f, passBox.getPosition().y + 10.f});
        window.draw(passDisplay);
    }
}

