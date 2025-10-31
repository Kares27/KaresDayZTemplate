// ============================================================
// COOKCRAFTER MENU - CUSTOM UI SCRIPTED MENU
// ============================================================
//
// Klasa głównego menu CookCraftera. Rozszerza UIScriptedMenu
// aby uzyskać automatyczne lifecycle management od UIManager.
//
// LIFECYCLE:
// 1. new CookCrafterMenu() - konstruktor
// 2. Init() - wołany przez UIManager, ładuje layout
// 3. OnShow() - wołany gdy menu ma być widoczne
// 4. Update(), OnClick(), OnKeyDown() - interakcje
// 5. OnHide() - wołany gdy menu się zamyka
//
// ============================================================

class CookCrafterMenu extends UIScriptedMenu
{
    // Ścieżka do pliku layoutu UI
    // Layout definiuje wizualną strukturę menu (buttony, teksty, etc.)
    static const string LAYOUT_FILE = "CookCrafter/gui/CookCrafterOverlay.layout";
    
    // Referencje do UI elementów ze layoutu
    // Będą wypełnione w Init()
    ref ButtonWidget m_CloseButton;
    ref ButtonWidget m_CloseButtonX;
    
    // --------------------------------------------------------
    // KONSTRUKTOR
    // --------------------------------------------------------
    // Wołany gdy new CookCrafterMenu() jest wykonane
    // Tutaj robimy minimalne inicjalizacje
    void CookCrafterMenu()
    {
        Print("[CookCrafter] CookCrafterMenu() - konstruktor");
    }
    
    // --------------------------------------------------------
    // INIT - WOŁANY AUTOMATYCZNIE PRZEZ UIMANAGER
    // --------------------------------------------------------
    // Odpowiedzialny za:
    // 1. Załadowanie layoutu z pliku .layout
    // 2. Znalezienie UI elementów (buttons, texts, etc.)
    // 3. Zwrócenie widget root do UIManager
    //
    // WAŻNE: layoutRoot musi być przypisany - to base class property!
    override Widget Init()
    {
        Print("[CookCrafter] Init() - inicjalizacja menu");
        
        // Ładowanie layoutu z pliku
        // CreateWidgets() parsuje XML i tworzy widget hierarchy
        layoutRoot = GetGame().GetWorkspace().CreateWidgets(LAYOUT_FILE);
        
        if (layoutRoot)
        {
            // Znalezienie buttonów ze layoutu
            // FindAnyWidget szuka recursively po nazwie w hierarchii
            m_CloseButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("CloseButton"));
            m_CloseButtonX = ButtonWidget.Cast(layoutRoot.FindAnyWidget("CloseButtonX"));
            
            Print("[CookCrafter] Init() - Layout załadowany");
            Print("[CookCrafter] CloseButton znaleziony: " + (m_CloseButton != NULL));
            Print("[CookCrafter] CloseButtonX znaleziony: " + (m_CloseButtonX != NULL));
        }
        else
        {
            Print("[CookCrafter] BŁĄD: Init() - layoutRoot jest NULL! Sprawdź ścieżkę: " + LAYOUT_FILE);
        }
        
        // Zwrócenie root widget - UIManager używa go do zarządzania menu
        return layoutRoot;
    }
    
    // --------------------------------------------------------
    // ONSHOW - WOŁANY GDY MENU SIĘ OTWIERA
    // --------------------------------------------------------
    // Odpowiedzialny za:
    // 1. Pokazanie layoutu
    // 2. Ustawienie focusa
    // 3. Przełączenie gry w tryb UI
    // 4. Wyłączenie gracza / pokazanie cursora
    override void OnShow()
    {
        super.OnShow();
        
        Print("[CookCrafter] OnShow() - menu się otwiera");
        
        // Upewnienie się że layout jest widoczny
        // (layout może mieć visible="0" w pliku .layout)
        if (layoutRoot)
        {
            layoutRoot.Show(true);
        }
        
        // Ustawienie focusa - menu otrzymuje input events
        SetFocus(layoutRoot);
        
        // Przełączenie gry w tryb UI (graacz nie steruje postacią)
        GetGame().GetInput().ChangeGameFocus(1);
        
        // Pokazanie cursora myszy
        GetGame().GetUIManager().ShowCursor(true);
        
        // Wyłączenie gracza aby się nie ruszał podczas menu
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player)
            player.GetInputController().SetDisabled(true);
        
        Print("[CookCrafter] OnShow() - menu gotowe do interakcji");
    }
    
    // --------------------------------------------------------
    // ONHIDE - WOŁANY GDY MENU SIĘ ZAMYKA
    // --------------------------------------------------------
    // Odpowiedzialny za:
    // 1. Ukrycie layoutu
    // 2. Przełączenie gry z powrotem w tryb gameplay
    // 3. Włączenie gracza / ukrycie cursora
    override void OnHide()
    {
        super.OnHide();
        
        Print("[CookCrafter] OnHide() - menu się zamyka");
        
        // Ukrycie layoutu
        if (layoutRoot)
        {
            layoutRoot.Show(false);
        }
        
        // Przełączenie z powrotem do gameplaymu
        GetGame().GetInput().ResetGameFocus();
        
        // Ukrycie cursora myszy
        GetGame().GetUIManager().ShowCursor(false);
        
        // Włączenie sterowania graczem
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player)
            player.GetInputController().SetDisabled(false);
        
        Print("[CookCrafter] OnHide() - gameplay wznowiony");
    }
    
    // --------------------------------------------------------
    // ONCLICK - OBSŁUGA KLIKNIĘCIA MYSZY
    // --------------------------------------------------------
    // Wołany gdy gracz klika na widget w menu
    override bool OnClick(Widget w, int x, int y, int button)
    {
        // Obsługa lewego przycisku myszy
        if (button == MouseState.LEFT)
        {
            // Sprawdzenie czy kliknięto przycisk zamknięcia
            if (w == m_CloseButton || w == m_CloseButtonX)
            {
                Print("[CookCrafter] OnClick() - przycisk Close kliknięty");
                // Close() wyzwoli OnHide() i usunie menu
                Close();
                return true;  // Zapewnienie że event został obsłużony
            }
        }
        
        // Przekazanie nieobsłużonych eventów do parent class
        return super.OnClick(w, x, y, button);
    }
    
    // --------------------------------------------------------
    // ONKEYDOWN - OBSŁUGA NACIŚNIĘCIA KLAWISZA
    // --------------------------------------------------------
    // Wołany gdy gracz naciśnie klawisz podczas menu
    override bool OnKeyDown(Widget w, int x, int y, int key)
    {
        // Zamykanie menu na ESC
        if (key == KeyCode.KC_ESCAPE)
        {
            Print("[CookCrafter] OnKeyDown() - ESC naciśnięty, zamykanie menu");
            Close();
            return true;
        }
        
        return super.OnKeyDown(w, x, y, key);
    }
    
    // --------------------------------------------------------
    // ONMOUSEENTER - OBSŁUGA NAJECHANIA MYSZĄ
    // --------------------------------------------------------
    // Wołany gdy gracz najechże myszą na widget
    // (Tu głównie do debugowania, można usunąć)
    override bool OnMouseEnter(Widget w, int x, int y)
    {
        // Proste debug info przy najechaniu na widgety
        // Print("[CookCrafter] OnMouseEnter() - " + w.GetName());
        return super.OnMouseEnter(w, x, y);
    }
};