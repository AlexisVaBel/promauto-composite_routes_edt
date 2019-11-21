#include "uitodbtable.h"

UIToDBTable::UIToDBTable(RoutesUI *ui, std::shared_ptr<IDataProvider> provider):m_ui(ui),
    m_provider(provider)
{    
}


