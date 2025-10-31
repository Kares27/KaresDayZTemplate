// ============================================================
// MISSION BASE MOD - FACTORY PATTERN DLA MENU
// ============================================================
// 
// Override CreateScriptedMenu() pozwala na tworzenie custom menu
// poprzez ID zamiast hard-codowania.
//
// Flow:
// 1. ShowOverlay() wołane z CookCrafterHelperImpl
// 2. UIManager.EnterScriptedMenu(ID) szuka czy ID istnieje
// 3. Jeśli nie, wołany jest CreateScriptedMenu(ID) z tej klasy
// 4. Zwracamy nową instancję CookCrafterMenu
// 5. UIManager automatycznie wołana Init(), OnShow() etc.
// 
// Wzorzec wzięty z ZenSplitItemUI moda
// ============================================================

modded class MissionBase
{
    // --------------------------------------------------------
    // Override - tworzy menu na podstawie ID
    // --------------------------------------------------------
    override UIScriptedMenu CreateScriptedMenu(int id)
    {
        // Najpierw wołamy super - może to być vanilla menu
        UIScriptedMenu menu = super.CreateScriptedMenu(id);

        // Jeśli super nie obsługuje tego ID, tworzymy nasz custom
        if (!menu)
        {
            switch (id)
            {
                // Obsługa menu CookCrafterMenu
                case MENU_COOKCRAFTER:
                {
                    Print("[CookCrafter] CreateScriptedMenu() - tworzenie CookCrafterMenu");
                    menu = new CookCrafterMenu();
                    break;
                }
            }
        }

        return menu;
    }
}