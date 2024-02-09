

#include "UnitTest_Utilities.h"
#include "lib3mf_implicit.hpp"

#include <cmath>

namespace Lib3MF
{
	char const * testOptimizationUUID = "ea758a2c-dec9-4406-9829-1232b758d155";

	PModel writeAndRead(PWrapper wrapper, PModel original) {
		PWriter writer = original->QueryWriter("3mf");
		std::vector<Lib3MF_uint8> buffer;
		writer->WriteToBuffer(buffer);
		PModel model = wrapper->CreateModel();
		PReader reader = model->QueryReader("3mf");
		reader->ReadFromBuffer(buffer);
		int warnCount = reader->GetWarningCount();
		if (0 != warnCount)
			throw std::runtime_error("warnings present");
		return model;
	}

	void WriteAndCheck(PWrapper wrapper, PModel model) {
		auto newModel = writeAndRead(wrapper, model);
		ASSERT_TRUE(newModel->HasOptimization());
		for (PBuildItemIterator iterator = newModel->GetBuildItems(); iterator->MoveNext();) {
			PBuildItem item = iterator->GetCurrent();
			ASSERT_TRUE(item->HasOptimization());
		}
	}

	class OptimizationInMultipleBox : public ::testing::Test {
	protected:

		virtual void SetUp() {
			model = wrapper->CreateModel();
			reader = model->QueryReader("3mf");
			reader->ReadFromFile(sTestFilesPath + "/Optimization/multiple_box.3mf");
			ASSERT_EQ(0, reader->GetWarningCount());
		}
		virtual void TearDown() {
			model.reset();
		}

		void setOptimization() {
			model->SetOptimizationUUID(testOptimizationUUID);
			model->SetOptimizationMode(eOptimizationMode::Incremental);
			ASSERT_TRUE(model->HasOptimization());
		}

		PModel model;
		PReader reader;
		PWriter writer;

		POptimization optimization;
		PResource resource;

		static void SetUpTestCase() {
			wrapper = CWrapper::loadLibrary();
		}
		static PWrapper wrapper;
	};
	PWrapper OptimizationInMultipleBox::wrapper;

	TEST_F(OptimizationInMultipleBox, HasSetClearOptimization)
	{
		setOptimization();
		ASSERT_TRUE(model->HasOptimization());
		PModel newModel = writeAndRead(wrapper, model);
		ASSERT_TRUE(model->HasOptimization());
	}

	TEST_F(OptimizationInMultipleBox, WorkWithMultipleOptimizations)
	{
		setOptimization();

		PBuildItemIterator iterator = model->GetBuildItems();
		//skip one
		ASSERT_TRUE(iterator->MoveNext());

		auto opt1 = model->AddOptimization();
		ASSERT_TRUE(iterator->MoveNext());
		{
			sOptimizationParam param1 = { 1.047f, 1.0053f, 0.998f, 0.00125f, 0.003456f, 0.00982f };
			auto item = iterator->GetCurrent();
			int index = opt1->AddOptimizationParam(param1);
			item->AssignOptimizationParam(opt1->GetResourceID(), index);
			ASSERT_TRUE(item->HasOptimization());
		}

		ASSERT_TRUE(iterator->MoveNext());
		{
			sOptimizationParam param1 = { 1.047f, 1.0053f, 0.998f, 0.00125f, 0.003456f, 0.00982f };
			auto item = iterator->GetCurrent();
			int index = opt1->AddOptimizationParam(param1);
			item->AssignOptimizationParam(opt1->GetResourceID(), index);
			ASSERT_TRUE(item->HasOptimization());
		}

		auto opt2 = model->AddOptimization();
		ASSERT_TRUE(iterator->MoveNext());
		{
			sOptimizationParam param2 = { 1.045f, 1.0055f, 0.995f, 0.00120f, 0.003450f, 0.00980f };
			auto item = iterator->GetCurrent();
			int index = opt2->AddOptimizationParam(param2);
			item->AssignOptimizationParam(opt2->GetResourceID(), index);
			ASSERT_TRUE(item->HasOptimization());
		}

		ASSERT_TRUE(iterator->MoveNext());
		{
			sOptimizationParam param2 = { 1.045f, 1.0055f, 0.995f, 0.00120f, 0.003450f, 0.00980f };
			auto item = iterator->GetCurrent();
			int index = opt2->AddOptimizationParam(param2);
			item->AssignOptimizationParam(opt2->GetResourceID(), index);
			ASSERT_TRUE(item->HasOptimization());
		}

		auto optimizations = model->GetOptimizations();
		ASSERT_EQ(2, optimizations->Count());

		PModel newModel = writeAndRead(wrapper, model);

		ASSERT_TRUE(newModel->HasOptimization());
		POptimizationIterator newOptimizations = newModel->GetOptimizations();
		ASSERT_EQ(2, newOptimizations->Count());

		PBuildItemIterator newIterator = newModel->GetBuildItems();
		ASSERT_TRUE(newIterator->MoveNext());
		{
			PBuildItem newItem = newIterator->GetCurrent();
			ASSERT_FALSE(newItem->HasOptimization());
		}

		while (newIterator->MoveNext()) {
			PBuildItem newItem = newIterator->GetCurrent();
			ASSERT_TRUE(newItem->HasOptimization());
		}
	}

	TEST_F(OptimizationInMultipleBox, WorkWithParams)
	{
		auto optimization = model->AddOptimization();
		sOptimizationParam params[3] = { 
			{ 1.047f, 1.0053f, 0.998f, 0.00125f, 0.003456f, 0.00982f },
			{ 1.048f, 1.0054f, 0.999f, 0.00126f, 0.003457f, 0.00983f },
			{ 1.049f, 1.0055f, 0.9991f, 0.00127f, 0.003458f, 0.00984f } };
		optimization->AddOptimizationParam(params[0]);
		optimization->AddOptimizationParam(params[1]);
		optimization->AddOptimizationParam(params[2]);

		PModel newModel = writeAndRead(wrapper, model);

		POptimizationIterator iterator = newModel->GetOptimizations();
		ASSERT_TRUE(iterator->MoveNext());
		POptimization newOptimization = iterator->GetCurrentOptimization();
		for (int i = 0; i < 3; i++) {
			ASSERT_EQ(newOptimization->GetOptimizationParam(i).m_OffsetX, params[i].m_OffsetX);
			ASSERT_EQ(newOptimization->GetOptimizationParam(i).m_OffsetY, params[i].m_OffsetY);
			ASSERT_EQ(newOptimization->GetOptimizationParam(i).m_OffsetZ, params[i].m_OffsetZ);
			ASSERT_EQ(newOptimization->GetOptimizationParam(i).m_ScalingX, params[i].m_ScalingX);
			ASSERT_EQ(newOptimization->GetOptimizationParam(i).m_ScalingY, params[i].m_ScalingY);
			ASSERT_EQ(newOptimization->GetOptimizationParam(i).m_ScalingZ, params[i].m_ScalingZ);
		}
	}

	class OptimizationFromExistingFile : public ::testing::Test {
	protected:
		virtual void SetUp() {
			model = wrapper->CreateModel();
			reader = model->QueryReader("3mf");
			writer = model->QueryWriter("3mf");
		}
		virtual void TearDown() {
			model.reset();
		}

		PModel model;
		PReader reader;
		PWriter writer;


		virtual void AddOptimization() {
			model->SetOptimizationMode(eOptimizationMode::Incremental);
			model->SetOptimizationUUID("8958bf59-3bd2-4d2d-88a2-e64d3ddf5839");
			POptimization optimization = model->AddOptimization();
			for (PBuildItemIterator iterator = model->GetBuildItems(); iterator->MoveNext();) {
				sOptimizationParam param = { 1.012f, 1.012f, 1.012f, 0.05f, 0.05f, 0.05f };
				int index = optimization->AddOptimizationParam(param);
				PBuildItem item = iterator->GetCurrent();
				item->AssignOptimizationParam(optimization->GetResourceID(), index);
			}
		}

		static void SetUpTestCase() {
			wrapper = CWrapper::loadLibrary();
		}
		static PWrapper wrapper;
	};
	PWrapper OptimizationFromExistingFile::wrapper;

	TEST_F(OptimizationFromExistingFile, ReadJustWriteAndReadZeroWarning) 
	{
		reader->ReadFromFile(sTestFilesPath + "/Optimization/box.3mf");
		ASSERT_FALSE(model->HasOptimization());
		std::vector<Lib3MF_uint8> buffer;
		writer->WriteToBuffer(buffer);
		auto newModel = wrapper->CreateModel();
		auto newReader = newModel->QueryReader("3mf");
		newReader->ReadFromBuffer(buffer);
		ASSERT_EQ(0, newReader->GetWarningCount());
		ASSERT_FALSE(newModel->HasOptimization());
	}

	TEST_F(OptimizationFromExistingFile, AddOptimizationExistingFileSingleItem) 
	{
		reader->ReadFromFile(sTestFilesPath + "/Optimization/box.3mf");
		ASSERT_EQ(0, reader->GetWarningCount());
		ASSERT_FALSE(model->HasOptimization());
		AddOptimization();
		WriteAndCheck(wrapper, model);
	}

	TEST_F(OptimizationFromExistingFile, AddOptimizationExistingFileMultipleItem) 
	{
		reader->ReadFromFile(sTestFilesPath + "/Optimization/multiple_box.3mf");
		ASSERT_EQ(0, reader->GetWarningCount());
		ASSERT_FALSE(model->HasOptimization());
		AddOptimization();
		WriteAndCheck(wrapper, model);
	}

	TEST_F(OptimizationFromExistingFile, AddOptimizationExistingFileItemIsComponent) 
	{
		reader->ReadFromFile(sTestFilesPath + "/Optimization/multiple_box_components.3mf");
		ASSERT_EQ(0, reader->GetWarningCount());
		ASSERT_FALSE(model->HasOptimization());
		AddOptimization();
		WriteAndCheck(wrapper, model);
	}

	TEST_F(OptimizationFromExistingFile, AddOptimizationExistingFileItemIsComponentAggregation) {
		reader->ReadFromFile(sTestFilesPath + "/Optimization/multiple_box_component_aggregation.3mf");
		ASSERT_EQ(0, reader->GetWarningCount());
		ASSERT_FALSE(model->HasOptimization());
		AddOptimization();
		WriteAndCheck(wrapper, model);
	}

	TEST_F(OptimizationFromExistingFile, ReadExistingOptimization)
	{
		reader->ReadFromFile(sTestFilesPath + "/Optimization/optimized_box.3mf");
		ASSERT_EQ(0, reader->GetWarningCount());
		ASSERT_TRUE(model->HasOptimization());
		ASSERT_EQ(model->GetOptimizationUUID(), "8958bf59-3bd2-4d2d-88a2-e64d3ddf5839");

		for (PBuildItemIterator iterator = model->GetBuildItems(); iterator->MoveNext();) {
			PBuildItem item = iterator->GetCurrent();
			ASSERT_TRUE(item->HasOptimization());
			Lib3MF_uint32 optimizationId = item->GetOptimizationID();
			Lib3MF_int32 optimizationIndex = item->GetOptimizationIndex();
			POptimization optimization = model->GetOptimizationByID(optimizationId);
			ASSERT_TRUE(optimization != nullptr);
			sOptimizationParam params = optimization->GetOptimizationParam(optimizationIndex);
			ASSERT_EQ(params.m_OffsetX, 0.05f);
		}
	
	}

	TEST_F(OptimizationFromExistingFile, ReadExistingNoOptimizationUUIDMustNotWarn) {
		reader->ReadFromFile(sTestFilesPath + "/Optimization/optimized_box_no_optimizationuuid.3mf");
		ASSERT_EQ(0, reader->GetWarningCount());
		ASSERT_FALSE(model->HasOptimization());
	}

	TEST_F(OptimizationFromExistingFile, ReadExistingOptimizatizationIdIsZeroMustWarn) {
		reader->ReadFromFile(sTestFilesPath + "/Optimization/optimized_box_zero_optimizationid.3mf");
		ASSERT_EQ(1, reader->GetWarningCount());
	}

	TEST_F(OptimizationFromExistingFile, ReadExistingOptimizatizationIndexButNoOptimizationIdMustWarn) {
		reader->ReadFromFile(sTestFilesPath + "/Optimization/optimized_box_extra_optimizationindex.3mf");
		ASSERT_EQ(1, reader->GetWarningCount());
	}

}

