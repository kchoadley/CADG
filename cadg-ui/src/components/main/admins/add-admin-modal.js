import React, { Component } from 'react';
import {
  Button,
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
  render() {
    return (
      <div>
        <Form>

        <Modal isOpen={this.props.isAdding} toggle={this.props.toggle}>
          <ModalHeader toggle={this.props.toggle}>Add Administrator</ModalHeader>
          <ModalBody>
              <Row form>
                <Col md={6}>
                  <FormGroup>
                    <Label for='given-name'>First Name</Label>
                    <Input type='text' name='given-name' id='first_name'/>
                  </FormGroup>
                </Col>
                <Col md={6}>
                  <FormGroup>
                    <Label for='family-name'>Last Name</Label>
                    <Input type='text' name='family-name' id='last_name'/>
                  </FormGroup>
                </Col>
              </Row>

              <Row form>
                <Col md={6}>
                  <FormGroup>
                    <Label for='email'>Email</Label>
                    <Input type='email' name='email' id='email'/>
                  </FormGroup>
                </Col>
                <Col md={6}>
                  <FormGroup>
                    <Label for='phone'>Phone</Label>
                    <Input type='phone' name='phone' id='phone'/>
                  </FormGroup>
                </Col>
              </Row>

              <FormGroup >
                <Label for='username'>Username</Label>
                <Input type='text' name='username' id='username'/>
              </FormGroup>

              <FormGroup>
                <Label for="address">Address</Label>
                <Input type="text" name="address" id="address" placeholder='1234 Main St.'/>
              </FormGroup>
              <Row form>
                <Col md={5}>
                  <FormGroup>
                    <Label for="state">City/State/Region</Label>
                    <Input type="text" name="state" id="state_region" placeholder='New York, NY'/>
                  </FormGroup>
                </Col>
                <Col md={4}>
                  <FormGroup>
                    <Label for="country">Country</Label>
                    <Input type="text" name="country" id="country" placeholder='USA'/>
                  </FormGroup>
                </Col>
                <Col md={3}>
                  <FormGroup>
                    <Label for="zip">Zip</Label>
                    <Input type="text" name="zip" id="zip" placeholder='12345'/>
                  </FormGroup>
                </Col>
              </Row>
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
