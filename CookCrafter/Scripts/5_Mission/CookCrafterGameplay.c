// ============================================================
// MENU CONSTANT
// ============================================================
// Unique identifier dla CookCrafterMenu, używany przez UIManager
// do rozpoznawania i tworzenia menu przez CreateScriptedMenu()
const int MENU_COOKCRAFTER = -84756239;

// ============================================================
// MISSION GAMEPLAY MOD
// ============================================================
modded class MissionGameplay
{
    void MissionGameplay()
    {
        // Inicjalizacja CookCrafterHelper - singleton pattern
        // Pozwala na wołanie ShowOverlay() z dowolnego miejsca w grze
        CookCrafterHelperImpl impl = new CookCrafterHelperImpl();
        CookCrafterHelper.SetInstance(impl);
    }
}

// ============================================================
// COOKCRAFTER HELPER IMPLEMENTATION
// ============================================================
// Klasa implementująca CookCrafterHelper z logika otwierania/zamykania menu
// 
// Wzorzec:
// 1. ShowOverlay() wołane z jakiegoś triggera (np. po skoku) 
// 2. EnterScriptedMenu(ID) tworzy menu przez CreateScriptedMenu() override
// 3. UIManager zwraca gotową instancję z wywolanymi Init(), OnShow() etc.
// 4. Referencja do m_Menu pozwala na później wołanie HideOverlay()
class CookCrafterHelperImpl extends CookCrafterHelper
{
    // Referencja do menu - musi być przechowywana aby uniknąć garbage collection
    // zanim lifecycle methods się wykonają
    ref CookCrafterMenu m_Menu;
    
    // --------------------------------------------------------
    // Otwiera menu CookCrafterMenu gdy trigger się aktywuje
    // --------------------------------------------------------
    override void ShowOverlay()
    {
        Print("[CookCrafter] ShowOverlay() - otwieranie menu");
        
        // Sprawdzenie czy menu już istnieje (aby uniknąć duplikatów)
        if (m_Menu)
        {
            Print("[CookCrafter] Menu już otwarte, ignorowanie");
            return;
        }
        
        // Wołanie EnterScriptedMenu() z ID menu
        // To wyzwoli CreateScriptedMenu(MENU_COOKCRAFTER) override w MissionBase
        // który utworzy nową instancję CookCrafterMenu
        CookCrafterMenu gui = CookCrafterMenu.Cast(
            GetGame().GetUIManager().EnterScriptedMenu(MENU_COOKCRAFTER, GetGame().GetUIManager().GetMenu())
        );
        
        if (gui)
        {
            // Zapisanie referencji - inaczej zostałoby garbage collected!
            m_Menu = gui;
            Print("[CookCrafter] Menu otwarte pomyślnie");
            Print("[CookCrafter] Init() i OnShow() zostały automatycznie wywołane przez UIManager");
        }
        else
        {
            Print("[CookCrafter] BŁĄD: Nie udało się utworzyć menu!");
        }
    }
    
    // --------------------------------------------------------
    // Zamyka menu CookCrafterMenu
    // --------------------------------------------------------
    override void HideOverlay()
    {
        Print("[CookCrafter] HideOverlay() - zamykanie menu");
        
        if (m_Menu)
        {
            // Close() wyzwoli OnHide() i usunie menu z UIManager
            m_Menu.Close();
            m_Menu = NULL;  // Wyczyszczenie referencji
            Print("[CookCrafter] Menu zamknięte");
        }
        else
        {
            Print("[CookCrafter] Menu już zamknięte, ignorowanie");
        }
    }
};