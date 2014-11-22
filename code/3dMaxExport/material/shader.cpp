// test.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

//#include <stdio.h>
//#include <math.h>
//#include <shader.h>


typedef struct {
	miBoolean	mask;
	miBoolean	Reflection;
	miBoolean	Refraction;
	miScalar	IOR;
} qkcolimo_t;

extern "C" {
    DLLEXPORT int qkcolimo_version(void) {return(1);}


    DLLEXPORT miBoolean qkcolimo(miColor *result,miState *state,qkcolimo_t *param)
    {
	   miBoolean mask = *mi_eval_boolean(&param->mask);
	   miBoolean Reflection = *mi_eval_boolean(&param->Reflection);
	   miBoolean Refraction = *mi_eval_boolean(&param->Refraction);
	   miScalar IOR = *mi_eval_scalar(&param->IOR);
	   miColor temp;
	   miScalar save_ior;
	   miScalar in_ior;
	   miScalar out_ior;
	   miVector	dir;
	   miBoolean	ok;
	   miVector    v;
	   miVector    p;

	   if (state->type == miRAY_SHADOW || state->type == miRAY_DISPLACE ) {
		return(miFALSE);
	   }
	   p=state->tex_list[0];//获取纹理坐标
	   while(p.x>1)
	   {
		  p.x-=1.0f;
	   }//只取纹理坐标的小数部分
	   while(p.y>1)
	   {
		  p.y-=1.0f;
	   }//取小数部分
		result->r=mask?p.x:0.0f;
		result->g=mask?p.y:0.0f;
		result->b=mask?1.0f:0.0f;//将纹理坐标保存到最终结果

		//state->reflection_level：当前的反射次数
	   if (Reflection&&state->reflection_level<1)
	   {
		  save_ior   = state->ior;
		  state->ior = state->ior_in;
	       mi_reflection_dir(&dir, state);
		  ok = mi_trace_reflection(&temp, state, &dir);
		  if (!ok) 
		  {
			 temp.r=0;
			 temp.g=0;
			 temp.b=0;
		  }

		  //if already has uv then not add more uv
		  if(!(result->r > 0.0f || result->g > 0.0f)){
			  result->r+=temp.r;
			  result->g+=temp.g;
			  result->b+=temp.b;
		  }

		  state->ior = save_ior;
	   }
	   if (Refraction&&state->refraction_level<3)
	   {
		  if (IOR == 0.0 || IOR == 1.0)
			mi_trace_transparent(&temp, state);
		  else
		  {
			 if (state->inv_normal)
			 {
				in_ior=IOR;
				out_ior=1.0;
			 }
			 else
			 {
				in_ior=1.0;
				out_ior=IOR;
			 }
			 if (mi_refraction_dir(&dir, state, in_ior, out_ior))
				mi_trace_refraction(&temp, state, &dir);
			else {//全反射
			    if(state->reflection_level<1)
			    {
				    mi_reflection_dir(&dir, state);
				    mi_trace_reflection(&temp, state, &dir);
			    }
			}
			 
		  }

		  //if already has uv then not add more uv
		  if(!(result->r > 0.0f || result->g > 0.0f)){
			  result->r+=temp.r;
			  result->g+=temp.g;
			  result->b+=temp.b;
		  }
	   }
	   result->a = 1;
	   return(miTRUE);
    }
}
