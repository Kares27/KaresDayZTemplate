// Hook do PlayerBase - pokazuje overlay gdy gracz skoczy
modded class PlayerBase
{
    override void OnJumpEnd(int pLandType = 0)
    {
        super.OnJumpEnd(pLandType);

        // Tylko na kliencie i tylko dla kontrolowanego gracza
        if (GetGame().IsClient() && GetGame().GetPlayer() == this)
        {
            Print("[CookCrafter] Jump detected - showing overlay 2.0");
            CookCrafterHelper.Get().ShowOverlay();
        }
    }
};