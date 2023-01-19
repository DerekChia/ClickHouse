#pragma once
#include <Processors/IProcessor.h>
#include <Processors/ResizeProcessor.h>

namespace DB
{

class RemoteQueryExecutor;
using RemoteQueryExecutorPtr = std::shared_ptr<RemoteQueryExecutor>;

class DependentProcessor : public IProcessor
{
public:
    using IProcessor::IProcessor;
    virtual void connectToScheduler(ResizeProcessor & scheduler) = 0;
};

class ReadFromMergeTreeDependencyTransform : public DependentProcessor
{
public:
    explicit ReadFromMergeTreeDependencyTransform(const Block & header);

    String getName() const override { return "ReadFromMergeTreeDependency"; }
    Status prepare() override;

    InputPort & getInputPort() { assert(data_port); return *data_port; }
    InputPort & getDependencyPort() { assert(dependency_port); return *dependency_port; }
    OutputPort & getOutputPort() { return outputs.front(); }

    void connectToScheduler(ResizeProcessor & scheduler) override;
private:
    bool has_data{false};
    Chunk chunk;

    InputPort * data_port{nullptr};
    InputPort * dependency_port{nullptr};

    Status prepareGenerate();
    Status prepareConsume();
};


}
