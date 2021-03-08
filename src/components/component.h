#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
private:
    /**
     * If true, the component doesn't change on the
     * hardware but changes in the simulator only.
     */
    bool simulated = false;

public:
    Component() {}
    ~Component() {}

    /**
     * Enable the sim mode. In sim mode, the
     * component doesn't change on the hardware
     * but changes in the simulator only.
     */
    virtual void enableSimMode() final;

    /**
     * Returns true if the sim mode is enabled.
     * In sim mode, the component doesn't change
     * on the hardware but changes in the simulator only.
     */
    bool isSimulated() { return simulated; }

protected:
    /**
     * Execute something when the sim mode is enabled.
     * In sim mode, the component doesn't change on
     * the hardware but changes in the simulator only.
     */
    virtual void willEnableSimMode() {}
};

#endif /* COMPONENT_H */
