#pragma once

#ifndef __MODERN_CPP_H
#define __MODERN_CPP_H

#define FUNC_INFO (printf("-------------------- Function %s --------------------\n", __func__));
#define SUBFUNC_INFO (printf("---------- Sub-Function %s ----------\n", __func__));
#define PASS_INFO(k) (printf("---------- Pass %u ----------\n", k));

void Ch01_DemoAuto();
void Ch01_DemoAlias();
void Ch01_DemoInitializerList();
void Ch01_DemoNonStaticMemberInitialization();
void Ch01_DemoAlignment();
void Ch01_DemoScopedEnumerations();
void Ch01_DemoOverride_Final_For_Virtual_Methods();
void Ch01_DemoRangeBasedForLoop();
void Ch01_DemoEnableRangeBasedForLoop4CustomTypes();
void Ch01_DemoCheckModules();
void Ch01_DemoExplicitConstructorAndConversionOperator();
void Ch01_DemoNamespace();
void Ch01_DemoNamespacesForSymbolVersioning();
void Ch01_DemoStructuredBindings();

void Ch02_DemoConvertingNumericStringTypes();
void Ch02_DemoNumberLimitsOtherProperties();
void Ch02_DemoGeneratingPseudoRandomNumbers();
void Ch02_DemoMonteCarloSimulation();
void Ch02_DemoStandardLiteralOperators();
void Ch02_DemoCreatingCookedUserDefinedLiterals();
void Ch02_DemoCreatingRawUserDefinedLiterals();
void Ch02_DemoCreatingStringLibraryHelpers();
void Ch02_DemoStringUsingRegularExpressions();
void Ch02_DemoParsingStringContentUsingRegularExpressions();
void Ch02_DemoReplacingStringContentUsingRegularExpressions();
void Ch02_DemoUsingStringViewInsteadConstantStringReferences();


void Ch08_DemoWorkingWithThreads();
void Ch08_DemoHandlingExceptionsFromThreadFunctions();
void Ch08_DemoSynchronizingAccessToSharedDataWithMutexesAndLocks();
void Ch08_DemoAvoidingUsingRecursiveMutexes();
void Ch08_DemoSendingNotificationsBetweenThreads();
void Ch08_DemoUsingPromisesAndFuturesFromThreads();
void Ch08_DemoExecutingFunctionsAsynchronously();
void Ch08_DemoUsingAtomicTypes();
void Ch08_DemoImplementingParallelMapWithThreads();
void Ch08_DemoImplementingParallelMapWithTasks();

void Ch03_DemoDefaultedAndDeletedFunctions();
void Ch03_DemoUsingLambdasWithStandardAlgorithms();
void Ch03_DemoUsingGenericLambdas();
void Ch03_DemoWritingRecursiveLambda();
void Ch03_DemoWritingFunctionTemplateWithVariableNumberArguments();
void Ch03_DemoComposingFunctionsIntoHigherOrderFunction();
void Ch03_DemoUniformlyInvokingAnythingCallable();

void Ch04_DemoConditionallyCompiling();
void Ch04_DemoPreprocessStringificationAndConcatenation();
void Ch04_DemoPerformingCompileTimeAssertionChecks();
void Ch04_DemoConditionallyCompilingClassFunctionsWithEnable_if();
void Ch04_DemoSelectingBranchesWithConstexpr_if();
void Ch04_DemoProvidingMetadataToCompilerWithAttributes();


void Ch05_DemoUsingVectorAsDefaultContainer();
void Ch05_DemoUsingBitsetForFixedSizeSequences();
void Ch05_DemoUsingVectorBoolForBitSequences();


#endif
