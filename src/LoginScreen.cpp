#include "LoginScreen.h"
using namespace sf;

LoginScreen::LoginScreen(const Font& font)
    : overlay(Vector2f(0.f, 0.f)),   // resize trong draw()
      card(Vector2f(460.f, 360.f)),
      title(font, L"Đăng nhập", 30),
      emailBox(Vector2f(360.f, 44.f)),
      passBox(Vector2f(360.f, 44.f)),
      btn(Vector2f(360.f, 44.f)),
      emailPH(font, L"Nhập email hoặc số điện thoại", 18),
      passPH(font, L"Nhập mật khẩu", 18),
      btnText(font, L"Tiếp tục", 20),
      linkForgot(font, L"Quên mật khẩu?", 16),
      linkCreate(font, L"Tạo tài khoản ngay", 16),
      closeX(font, L"X", 20)
{
    // overlay
    overlay.setFillColor(Color(0, 0, 0, 170));

    // card
    card.setFillColor(Color(255, 255, 255, 240));
    card.setOrigin(card.getSize() / 2.f);

    // title
    title.setFillColor(Color::Black);

    // email
    emailBox.setFillColor(Color(238, 238, 238));
    emailPH.setFillColor(Color(100, 100, 100));

    // password
    passBox.setFillColor(Color(238, 238, 238));
    passPH.setFillColor(Color(100, 100, 100));

    // button
    btn.setFillColor(Color(100, 149, 237));
    btnText.setFillColor(Color::White);

    // links
    linkForgot.setFillColor(Color(90, 90, 90));
    linkCreate.setFillColor(Color(36, 95, 180));

    // close X
    closeX.setFillColor(Color(90, 90, 90));
}

// ---- hàm update ----
bool LoginScreen::update(Vector2f mouse, bool mousePressed) {
    // click ra ngoài card -> đóng
    if (mousePressed && !card.getGlobalBounds().contains(mouse))
        return true;

    // click vào nút X -> đóng
    if (mousePressed && closeX.getGlobalBounds().contains(mouse))
        return true;

    return false; // chưa đóng
}

// ---- hàm draw ----
void LoginScreen::draw(RenderWindow& window) {
    auto size = window.getSize();
    overlay.setSize(Vector2f((float)size.x, (float)size.y));
    Vector2f center({size.x * 0.5f, size.y * 0.5f});
    card.setPosition(center);

    title.setPosition({center.x - 90.f, center.y - 150.f});

    emailBox.setPosition({center.x - 180.f, center.y - 88.f});
    emailPH.setPosition({emailBox.getPosition().x + 12.f, emailBox.getPosition().y + 10.f});

    passBox.setPosition({center.x - 180.f, center.y - 34.f});
    passPH.setPosition({passBox.getPosition().x + 12.f, passBox.getPosition().y + 10.f});

    btn.setPosition({center.x - 180.f, center.y + 22.f});
    btnText.setPosition({btn.getPosition().x + 125.f, btn.getPosition().y + 8.f});

    linkForgot.setPosition({center.x - 180.f, center.y + 78.f});
    linkCreate.setPosition({center.x - 180.f, center.y + 104.f});

    closeX.setPosition({
        card.getPosition().x + card.getSize().x / 2.f - 28.f,
        card.getPosition().y - card.getSize().y / 2.f + 8.f
    });

    // draw overlay + card
    window.draw(overlay);
    window.draw(card);

    // draw UI
    window.draw(title);
    window.draw(emailBox);   window.draw(emailPH);
    window.draw(passBox);    window.draw(passPH);
    window.draw(btn);        window.draw(btnText);
    window.draw(linkForgot); window.draw(linkCreate);
    window.draw(closeX);
}