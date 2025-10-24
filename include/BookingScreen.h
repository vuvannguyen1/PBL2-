#pragma once
#include <SFML/Graphics.hpp>
#include "HomeScreen.h"
#include "DetailScreen.h"
#include "Showtime.h"
#include <vector>
#include "Button.h"

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
    Font detailFont;
    BookingStep current_step;
    Text suat_chieu, ghe_ngoi, food, thanh_toan, xac_nhan;
    RectangleShape buttons_box[5];
    Texture tex;
    Sprite sprite;
    RectangleShape content_area;

    vector<Showtime> allShowtimes;
    vector<Showtime> showtimesForSelectedDate;
    vector<string> availableDates;
    string selectedDate;
    int currentMovieId;
    int selectedShowtimeIndex;

    vector<Button> dateButtons;
    vector<Button> timeButtons;
    
    // ✅ Action buttons: Xác nhận & Quay lại
    Button confirmButton;
    Button backButton;
    bool hasConfirmedShowtime; // Đã xác nhận suất chiếu chưa
    
    // ✅ Seat selection data
    vector<string> selectedSeats; // Danh sách ghế đã chọn (VD: "A1", "B5")
    static const int SEAT_ROWS = 9; // A-I
    static const int SEAT_COLS = 9; // 1-9
    vector<string> occupiedSeats; // Ghế đã được đặt (từ database/showtime)

    void drawStepContent(RenderWindow&);
    void drawDateSelection(RenderWindow&);
    void drawTimeSelection(RenderWindow&);
    void drawActionButtons(RenderWindow&); // Vẽ nút Xác nhận/Quay lại
    void drawSeatSelection(RenderWindow&); // Vẽ sơ đồ ghế
    void drawSeatSummary(RenderWindow&);   // Vẽ thông tin ghế đã chọn
    bool isSeatOccupied(const string& seat) const;
    bool isSeatSelected(const string& seat) const;
    void loadOccupiedSeatsFromSeatMap(const string& seat_map); // ✅ Load ghế đã đặt từ bitmap
    void saveSelectedSeatsToSeatMap(); // ✅ Lưu ghế đã chọn vào file
    void buildDateButtons();
    void buildTimeButtons();
    void updateShowtimesForSelectedDate(int, int, const string&);

    vector<Showtime> generateShowtimesForNext30Days(int);
public:
    BookingScreen(Font&);
    void handleEvent(const RenderWindow&, const Vector2f&, bool);
    void update(Vector2f, bool, AppState&); // ✅ Thêm tham số giống HomeScreen
    void draw(RenderWindow&);

    void loadFromDetail(const DetailScreen&);
};
