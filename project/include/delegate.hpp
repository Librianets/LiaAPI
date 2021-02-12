//-----------------------------------------------//-----------------------------------------------//
//--------------------------------------------/Class /--------------------------------------------//
//-----------------------------------------/Constructor /-----------------------------------------//
//----------------------------------/Constructor and Destructor/----------------------------------//
//--------------------------------------/Diagnostic options/--------------------------------------//
//------------------------------------------/Error code/------------------------------------------//
//--------------------------------------/Private variables /--------------------------------------//
//--------------------------------------/Private functions /--------------------------------------//
//---------------------------------------/Public functions/---------------------------------------//
//---------------------------------------/Public variables/---------------------------------------//


//class CDelegateStatic;
//class CDelegateMethod;


//class CInterfaseDelegate;
//class CDelegateStatic;
//class CDelegateMethod;








class CInterfaseDelegate
{	
public:
	virtual ~CInterfaseDelegate() {}
	virtual void Invoke() = 0;
	
private:
	



};

class CDelegateStatic: public CInterfaseDelegate
{
public:
	//~CDelegateStatic() {}
	typedef void (*typedlpFunc)();
	CDelegateStatic (typedlpFunc lpFunc_param)
		{lpFunc = lpFunc_param;}
	virtual void Invoke() { lpFunc(); }
	
private:
	typedlpFunc lpFunc;
};

CInterfaseDelegate *NewDelegate(void (*pFunc) () )
{
	return new CDelegateStatic(pFunc);
}

namespace funcemptydelegateclass
{
	void emptyfunc(void) {};
}

class CDelegate
{	
public:
	CDelegate() 
	{
		iSizePointClass = sizeof(this);
		iSizePointFuncClass = sizeof(&CDelegate::emptyfunc);
		iSizePointFunc = sizeof(&funcemptydelegateclass::emptyfunc);
	}
	~CDelegate() {}
	
	int iSizePointClass = 0;
	int iSizePointFuncClass = 0;
	int iSizePointFunc = 0;
	


private:
	void emptyfunc(void) {};
	//void empty(void) {iSizePointFuncClass = sizeof(*this);};

	int iCountDelegate = 0;
	




};







/*


class CDelegateMethod: public CInterfaseDelegate
{
public:
	~CDelegateMethod() {}
	
private:
	
};



class CDelegate
{
	CDelegate(CInterfaseDelegate * pDelegate = NULL)
	{
		
	}
	~CDelegate(){}
	
};






class IDelegateVoid
{
public:
  virtual ~IDelegateVoid() {}
  virtual void Invoke() = 0;
  virtual bool Compare(IDelegateVoid* pDelegate) = 0;
};

class CStaticDelegateVoid : public IDelegateVoid
{
public:
  typedef void (*PFunc)();
  CStaticDelegateVoid(PFunc pFunc) { m_pFunc = pFunc; }
  virtual void Invoke() { m_pFunc(); }
  virtual bool Compare(IDelegateVoid* pDelegate);

private:
  PFunc m_pFunc;
};

bool CStaticDelegateVoid::Compare(IDelegateVoid *pDelegate)
{
  CStaticDelegateVoid* pStaticDel = 
    dynamic_cast<CStaticDelegateVoid*>(pDelegate);

  if(pStaticDel == NULL || pStaticDel->m_pFunc != m_pFunc)
    return false;

  return true;
}

template<class TObj>
class CMethodDelegateVoid : public IDelegateVoid
{
public:
  typedef void (TObj::*PMethod)();
  CMethodDelegateVoid(TObj* pObj, PMethod pMethod)
  {
    m_pObj = pObj;
    m_pMethod = pMethod;
  }
  virtual void Invoke() { (m_pObj->*m_pMethod)(); }
  virtual bool Compare(IDelegateVoid* pDelegate);

private:
  TObj *m_pObj;
  PMethod m_pMethod;
};
 
template<class TObj>
bool CMethodDelegateVoid<TObj>::Compare(IDelegateVoid* pDelegate)
{
  CMethodDelegateVoid<TObj>* pMethodDel = 
    dynamic_cast<CMethodDelegateVoid<TObj>* >(pDelegate);

  if
  (
    pMethodDel == NULL ||
    pMethodDel->m_pObj != m_pObj ||
    pMethodDel->m_pMethod != m_pMethod
  )
    return false;

  return true;
}

/*IDelegateVoid* NewDelegate(void (*pFunc)())
{
  return new CStaticDelegateVoid(pFunc);
}

template <class TObj>
IDelegateVoid* NewDelegate(TObj* pObj, void (TObj::*pMethod)())
{
  return new CMethodDelegateVoid<TObj> (pObj, pMethod);
}*/

/*
class CDelegateVoid
{
public:
  CDelegateVoid(IDelegateVoid* pDelegate = NULL) { Add(pDelegate); }
  ~CDelegateVoid() { RemoveAll(); }
  bool IsNull() { return (m_DelegateList.size() == 0); }

  CDelegateVoid& operator=(IDelegateVoid* pDelegate)
  {
    RemoveAll();
    Add(pDelegate);
    return *this;
  }

  CDelegateVoid& operator+=(IDelegateVoid* pDelegate)
  {
    Add(pDelegate);
    return *this;
  }

  CDelegateVoid& operator-=(IDelegateVoid* pDelegate)
  {
    Remove(pDelegate);
    return *this;
  }

  void operator()()
  {
    Invoke();
  }
 
private:
  void Add(IDelegateVoid* pDelegate);
  void Remove(IDelegateVoid* pDelegate);
  void RemoveAll();
  void Invoke();

private:
  std::list<IDelegateVoid*> m_DelegateList;
};

void CDelegateVoid::Add(IDelegateVoid* pDelegate)
{
  if(pDelegate != NULL)
    m_DelegateList.push_back(pDelegate);
}

void CDelegateVoid::Remove(IDelegateVoid* pDelegate)
{
  std::list<IDelegateVoid*>::iterator it;
  for(it = m_DelegateList.begin(); it != m_DelegateList.end(); ++it)
  {
    if((*it)->Compare(pDelegate))
    {
      delete (*it);
      m_DelegateList.erase(it);
      break;
    }
  }

  delete pDelegate;
}

void CDelegateVoid::RemoveAll()
{
  std::list<IDelegateVoid*>::iterator it;
  for(it = m_DelegateList.begin(); it != m_DelegateList.end(); ++it)
    delete (*it);

  m_DelegateList.clear();
}

void CDelegateVoid::Invoke()
{
  std::list<IDelegateVoid*>::const_iterator it;
  for(it = m_DelegateList.begin(); it != m_DelegateList.end(); ++it)
    (*it)->Invoke();
}*/