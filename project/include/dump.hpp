////////////////////////////////////////////////////////////////////////////////
//// Liasteria (creative group). File created Librianets					////
//// Liasteria (творческая группа). Фаил создан Librianets					////
////																		////
//// Intellectual property rights belong Liasteria							////
//// Права на интеллектуальную собственность принадлежат Liasteria			////
//// 																		////
//// Use with copyright is permitted without agreement						////
//// Использование с сохраниением копирайта разрешается без согласования	////
//// 																		////
//// Programming is an art													////
//// Everyone has the right to creative freedom								////
//// I create as I see														////
////																		////
//// For all questions, as well as suggestions for improving the code:		////
//// По всем вопросам, а также с предложениями улучшения кода:				////
//// librianets@gmail.com													////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////// /////////////////////////////
////																		////
//// liasteria api - dump module											////
////																		////
////////////////////////////////////////////////////////////////////////////////

#ifndef DUMP_HPP
#define DUMP_HPP

namespace LIAPI
{
	
namespace DUMP
{
typedef void (*lp_func_other_class) (void);

extern void SigException(int signum);
extern void DumpStart (void);
extern void DumpStop (void);
extern void Test_Segmentation_Fault(void);
extern void ExecuteFunc (void);
extern void ResetFuncExec (void);
extern void DeleteFuncExec (void);
extern void AddFuncExec (void *AdressFunc);

} // namespace DUMP
} // namespace LIAPI
#endif //DUMP_HPP