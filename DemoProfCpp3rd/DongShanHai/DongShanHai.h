#pragma once

#define FUNC_INFO (printf("-------------------- Function %s --------------------\n", __func__));
#define SUBFUNC_INFO (printf("---------- Sub-Function %s ----------\n", __func__));
#define PASS_INFO(k) (printf("---------- Pass %u ----------\n", k));

void Ch06_DemoClassMemberInitializationOrder();
void Ch06_DemoStaticClassMember();
