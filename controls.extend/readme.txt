这里提供网友上传的扩展控件.
使用时先注册.
假定一个控件名为CTestCtrl
控件注册:
	TplDuiWindowFactory<CTestCtrl> *pFacTestCtrl= new TplDuiWindowFactory<CTestCtrl>;
	DuiWindowFactoryManager::getSingleton().RegisterFactory(pFacTestCtrl);
反注册:
	DuiWindowFactoryManager::getSingleton().UnregisterFactory(pFacTestCtrl);
	delete pFacTestCtrl;
