// RPC Constants
static const string COOKCRAFTER_RPC_NS = "CookCrafter";
static const string COOKCRAFTER_RPC_SHOW_OVERLAY = "ShowOverlay";
static const string COOKCRAFTER_RPC_HIDE_OVERLAY = "HideOverlay";

// Singleton Helper - dostępny ze wszystkich modułów
class CookCrafterHelper
{
    static ref CookCrafterHelper g_instance;
    
    static CookCrafterHelper Get()
    {
        if (!g_instance)
            g_instance = new CookCrafterHelper();
        return g_instance;
    }
    
    static void SetInstance(CookCrafterHelper impl)
    {
        g_instance = impl;
    }
    
    void ShowOverlay()
    {
        // Stub - będzie nadpisana w 5_Mission
    }
    
    void HideOverlay()
    {
        // Stub - będzie nadpisana w 5_Mission
    }
};