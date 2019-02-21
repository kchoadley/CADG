import React, { Component } from 'react';
import {
  Button,
  ButtonGroup,
  Modal,
  ModalHeader,
  ModalBody,
  ModalFooter,
  Form,
  FormGroup,
  Label,
  Input,
  Row,
  Col
} from 'reactstrap';

export default class Admins extends Component {
  constructor(props) {
    super(props);
    this.state = {
      selected: ''
    }
    this.onRadioBtnClick = this.onRadioBtnClick.bind(this);
  }

  onRadioBtnClick(rSelected) { this.setState({ rSelected }); }

  render() {
    return (
      <div>
        <Form>

        <Modal isOpen={this.props.isAdding} toggle={this.props.toggle}>
          <ModalHeader toggle={this.props.toggle}>Add Alert Originator Group</ModalHeader>
          <ModalBody>
            <Row form>
              <Col md={6}>
                <FormGroup>
                  <Label for='originator_name'>Name</Label>
                  <Input type='text' name='originator_name' id='originator_name'/>
                </FormGroup>
              </Col>
              <Col md={6}>
                <FormGroup>
                  <Label for='status'>Status</Label>
                  <ButtonGroup>
                    <Button
                      color='success'
                      onClick={() => this.onRadioBtnClick('ACTIVE')}
                      active={this.state.selected==='ACTIVE'}
                    >ACTIVE</Button>
                    <Button
                      color='danger'
                      onClick={() => this.onRadioBtnClick('DISABLED')}
                      active={this.state.selected==='DISABLED'}
                    >DISABLED</Button>
                  </ButtonGroup>
                </FormGroup>
              </Col>
            </Row>

            <FormGroup>
              <Label for='agency'>Agency</Label>
              <Input type='agency' name='agency' id='agency'/>
            </FormGroup>

          </ModalBody>
          <ModalFooter>
            <Button color="primary">Submit</Button>{' '}
            <Button color="secondary" onClick={this.props.toggle}>Cancel</Button>
          </ModalFooter>
        </Modal>
        </Form>
      </div>
    );
  }
}
